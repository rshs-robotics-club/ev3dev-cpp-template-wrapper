#include <bluetooth-socket.hpp>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/rfcomm.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <utilities.hpp>
#include <sys/ioctl.h>
#include <poll.h>

using namespace Ev3Wrap;

BluetoothSocket BluetoothSocket::CreateBluetoothSocket(std::string dest, bool awokenFirst) {
    return BluetoothSocket(dest, awokenFirst);
}

BluetoothSocket BluetoothSocket::CreateServerSocket() {
    return BluetoothSocket();
}

// equivalent to *BDADDR_ANY, but won't make compiler warnings
#define DEREF_BDADDR_ANY (bdaddr_t) {{0, 0, 0, 0, 0, 0}}

void BluetoothSocket::constructServerSocket() {
    this->mySocket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    struct sockaddr_rc localAddr = { 0 };
    localAddr.rc_family = AF_BLUETOOTH;
    localAddr.rc_bdaddr = DEREF_BDADDR_ANY;
    localAddr.rc_channel = (uint8_t) BLUETOOTH_PORT;
    bind(this->mySocket, (struct sockaddr *)&localAddr, sizeof(localAddr));
    listen(this->mySocket, BLUETOOTH_PORT);
}

void BluetoothSocket::constructClientSocket(std::string dest) {
    this->mySocket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    strcpy(this->otherSocketMAC, dest.c_str());
}

bool BluetoothSocket::attemptClientConnection(std::string dest) {
    std::string destination = dest;
    if (dest == "") {
        destination = std::string(this->otherSocketMAC);
    }
    else {
        strcpy(this->otherSocketMAC, destination.c_str());
    }
    struct sockaddr_rc addr = { 0 };
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) BLUETOOTH_PORT;
    str2ba(this->otherSocketMAC, &addr.rc_bdaddr);
    int status = connect(this->mySocket, (struct sockaddr*)&addr, sizeof(addr));
    if (status >= 0) {
        std::cout << "Bluetooth socket connection succeeded\n";
        this->otherSocket = this->mySocket;
        this->hasDisconnected = false;
        return true;
    }
    else {
        close(this->mySocket);
        this->mySocket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
        return false;
    }
}

bool BluetoothSocket::pollServerConnectionReady() {
    struct pollfd *pfd = (pollfd*)calloc(1, sizeof(*pfd));
    pfd[0].fd = this->mySocket;
    pfd[0].events = POLLIN;
    bool ret = (poll(pfd, 1, 5) != 0);
    free(pfd);
    return ret;
}

BluetoothSocket BluetoothSocket::CreateClientSocketByMAC(std::string MAC) {
    return BluetoothSocket(MAC, false);
}

BluetoothSocket::BluetoothSocket(bool useless) {
    std::cout << "dummy socket created\n";
}

BluetoothSocket BluetoothSocket::CreateDummySocket() {
    return BluetoothSocket(false);
}

BluetoothSocket::BluetoothSocket(std::string dest, bool awokenFirst) {
    this->awokenFirst = awokenFirst;
    this->hasDisconnected = false;
    if (awokenFirst) {
        // initialise into a server like thing
        this->constructServerSocket();
        std::cout << "waiting for other side to attempt connection\n";
        // loop until a connection is ready
        while (!this->pollServerConnectionReady()) {
            std::cout << "No connection attempt has been made yet...\n"; 
        }
        struct sockaddr_rc remoteAddr = { 0 };
        socklen_t opt = sizeof(remoteAddr);
        this->otherSocket = accept(this->mySocket, (struct sockaddr *)&remoteAddr, &opt);
        ba2str(&remoteAddr.rc_bdaddr, this->otherSocketMAC);
        std::cout << this->otherSocketMAC << " successfully connected\n";
    }
    else {
        if (dest == "") {
            std::string msg = "destionation bluetooth MAC address was not given!\n";
            throw std::system_error(std::make_error_code(std::errc::no_such_device_or_address), msg);
        }
        this->constructClientSocket(dest);
        while (true) {
            if (this->attemptClientConnection(dest)) {
                break;
            }
        }
    }
}

BluetoothSocket::~BluetoothSocket() {
    if (this->awokenFirst) {
        // otherSocket and mySocket are 2 different individual sockets which need to be closed
        close(this->otherSocket);
        close(this->mySocket);
    }
    else {
        // otherSocket and mySocket refer to the same thing
        close(this->mySocket);
    }
}

bool BluetoothSocket::send(char* msg, int size) {
    int status = write(this->otherSocket, msg, size);
    if (status == -1) {
        this->fireDisconnect();
    }
    return (status >= 0);
}

bool BluetoothSocket::readValue(char* msg, int size) {
    struct pollfd *pfds;
    int nfds = 1;
    pfds = (pollfd*)calloc(nfds, sizeof(*pfds));
    if (pfds == NULL) {
        std::string msg = "Calloc failed: unexpected behavior; pfds is equal to NULL\n";
        throw std::system_error(std::make_error_code(std::errc::not_enough_memory), msg);
    }
    pfds[0].fd = this->otherSocket;
    pfds[0].events = POLLIN;
    int ready;
    // block for 5 milliseconds
    ready = poll(pfds, nfds, 5);
    if (ready == 0) {
        // timed out, not ready
        free(pfds);
        return false;
    }
    else {
        if (pfds[0].revents & POLLERR) {
            // error when polling
            // very likely due to socket closed
            std::cout << "POLLERR\n";
            this->fireDisconnect();
            free(pfds);
            return false;
        }
        if (pfds[0].revents & POLLHUP) {
            // communication ended
            this->fireDisconnect();
            free(pfds);
            return false;
        }
        if (pfds[0].revents & POLLIN) {
            // read values
            int bytesRead;
            bytesRead = read(this->otherSocket, msg, size);
            if (bytesRead <= 0) {
                std::string msg = "POLLIN was detected however 0 bytes were read\n";
                throw std::system_error(std::make_error_code(std::errc::bad_message), msg);
            }
            free(pfds);
            return true;
        }
    }
}

BluetoothSocket BluetoothSocket::CreateClientSocketByHostname(std::string hostname) {
    int deviceId = hci_get_route(NULL);
    if (deviceId < 0) {
        std::string msg = "bluetooth adapter not found\n";
        throw std::system_error(std::make_error_code(std::errc::address_not_available), msg);
    }
    // find nearby devices
    int len = 8;
    int maxRsp = 255;
    int flags = IREQ_CACHE_FLUSH;
    inquiry_info* iInfs = (inquiry_info*)malloc(maxRsp * sizeof(inquiry_info));
    int socket = hci_open_dev(deviceId);
    if (socket < 0) {
        std::string msg = "Failed to open socket\n";
        throw std::system_error(std::make_error_code(std::errc::network_unreachable), msg);
    }
    while (true) {
        memset(iInfs, 0, maxRsp * sizeof(inquiry_info));
        int numRsp = hci_inquiry(deviceId, len, maxRsp, NULL, &iInfs, flags);
        if (numRsp < 0) {
            std::string msg = "hci_inquiry failed.\n";
            throw std::system_error(std::make_error_code(std::errc::network_unreachable), msg);
        }
        if (numRsp != 0) {
            // some are detected
            std::cout << "Found " << numRsp << " devices\n";
            int i;
            for (i = 0; i < numRsp; i++) {
                char deviceAddress[20], deviceName[300];
                inquiry_info* currentDevice = iInfs + i;
                memset(deviceAddress, 0, sizeof(deviceAddress));
                ba2str(&(currentDevice->bdaddr), deviceAddress);
                memset(deviceName, 0, sizeof(deviceName));
                if (hci_read_remote_name(socket, &(currentDevice->bdaddr), sizeof(deviceName), deviceName, 0) == -1) {
                    std::cout << "could not get remote name errno: " << errno << '\n';
                    continue;
                }
                else {
                    std::cout << deviceAddress << " | " << deviceName << " found\n";
                    std::string strDeviceName(deviceName, hostname.length());
                    if (strDeviceName == hostname) {
                        std::cout << "required address found. Connecting\n";
                        close(socket);
                        free(iInfs);
                        return BluetoothSocket(std::string(deviceAddress), false);
                    }
                }
            }
        }
    }
}

void BluetoothSocket::listDetectedDevices() {
    int deviceId = hci_get_route(NULL);
    if (deviceId < 0) {
        std::string msg = "bluetooth adapter not found\n";
        throw std::system_error(std::make_error_code(std::errc::address_not_available), msg);
    }
    // find nearby devices
    int len = 8;
    int maxRsp = 255;
    int flags = IREQ_CACHE_FLUSH;
    inquiry_info* iInfs = (inquiry_info*)malloc(maxRsp * sizeof(inquiry_info));
    int numRsp = hci_inquiry(deviceId, len, maxRsp, NULL, &iInfs, flags);
    if (numRsp < 0) {
        std::string msg = "hci_inquiry failed.\n";
        throw std::system_error(std::make_error_code(std::errc::network_unreachable), msg);
    }
    std::cout << "Found " << numRsp << " devices\n";
    int socket = hci_open_dev(deviceId);
    if (socket < 0) {
        std::string msg = "Failed to open socket\n";
        throw std::system_error(std::make_error_code(std::errc::network_unreachable), msg);
    }
    int i;
    for (i = 0; i < numRsp; i++) {
        char deviceAddress[20], deviceName[300];
        inquiry_info* currentDevice = iInfs + i;
        ba2str(&(currentDevice->bdaddr), deviceAddress);
        memset(deviceName, 0, sizeof(deviceName));
        if (hci_read_remote_name(socket, &(currentDevice->bdaddr), sizeof(deviceName), deviceName, 0) < 0) {
            strcpy(deviceName, "<unknown name>");
        }
        std::cout << deviceAddress << " | " << deviceName << '\n';
    }
    close(socket);
    free(iInfs);
}

void BluetoothSocket::fireDisconnect() {
    if (this->awokenFirst) {
        close(this->mySocket);
        close(this->otherSocket);
    }
    else {
        close(this->otherSocket);
    }
    this->mySocket = 0;
    this->otherSocket = 0;
    this->hasDisconnected = true;
    this->readyAttemptReconnect = false;
}

bool BluetoothSocket::attemptReconnect() {
    if (this->hasDisconnected == false) {
        std::string msg = "Bluetooth socket was told to reconnect even though it is already connected\n";
        throw std::system_error(std::make_error_code(std::errc::invalid_argument), msg);
    }
    if (this->readyAttemptReconnect) {
        if (this->awokenFirst) {
            // reactivate a server socket
            if (this->pollServerConnectionReady()) {
                // accept a socket
                struct sockaddr_rc remoteAddr = { 0 };
                socklen_t opt = sizeof(remoteAddr);
                this->otherSocket = accept(this->mySocket, (struct sockaddr *)&remoteAddr, &opt);
                ba2str(&remoteAddr.rc_bdaddr, this->otherSocketMAC);
                std::cout << this->otherSocketMAC << " reconnected\n";
                this->hasDisconnected = false;
                return true;
            }
            return false;
        }
        else {
            // reactivate a client socket
            return this->attemptClientConnection(std::string(this->otherSocketMAC));
        }
    }
    else {
        this->readyAttemptReconnect = true;
        if (this->awokenFirst) {
            // reactivate a server socket
            this->constructServerSocket();
        }
        else {
            // reactivate a client socket
            this->constructClientSocket(std::string(this->otherSocketMAC));
        }
        return false;
    }
}