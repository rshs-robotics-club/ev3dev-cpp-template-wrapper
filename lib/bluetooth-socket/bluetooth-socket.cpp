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

// equivalent to *BDADDR_ANY, but won't make compiler warnings
#define DEREF_BDADDR_ANY (bdaddr_t) {{0, 0, 0, 0, 0, 0}}

BluetoothSocket::BluetoothSocket(std::string dest, bool awokenFirst) {
    this->awokenFirst = awokenFirst;
    this->hasDisconnected = false;
    if (awokenFirst) {
        // initialise into a server like thing
        struct sockaddr_rc localAddr = { 0 };
        struct sockaddr_rc remoteAddr = { 0 };
        socklen_t opt = sizeof(remoteAddr);
        this->mySocket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
        localAddr.rc_family = AF_BLUETOOTH;
        localAddr.rc_bdaddr = DEREF_BDADDR_ANY;
        localAddr.rc_channel = (uint8_t) BLUETOOTH_PORT;
        bind(this->mySocket, (struct sockaddr *)&localAddr, sizeof(localAddr));
        listen(this->mySocket, BLUETOOTH_PORT);
        std::cout << "waiting for other side to attempt connection\n";
        // loop until a connection is ready
        struct pollfd *pfd = (pollfd*)calloc(1, sizeof(*pfd));
        pfd[0].fd = this->mySocket;
        pfd[0].events = POLLIN;
        int res = poll(pfd, 1, 5);
        std::cout << res << '\n';
        while (res == 0) {
            res = poll(pfd, 1, 5);
            std::cout << "No connection attempt has been made yet...\n"; 
        }
        free(pfd);

        this->otherSocket = accept(this->mySocket, (struct sockaddr *)&remoteAddr, &opt);
        this->otherSocketMAC = (char*)malloc(sizeof(char) * 18);
        ba2str(&remoteAddr.rc_bdaddr, this->otherSocketMAC);
        std::cout << this->otherSocketMAC << " successfully connected\n";
    }
    else {
        if (dest == "") {
            std::string msg = "destionation bluetooth MAC address was not given!\n";
            throw std::system_error(std::make_error_code(std::errc::no_such_device_or_address), msg);
        }
        
        char destination[18];
        strcpy(destination, dest.c_str());
        this->mySocket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
        while (true) {
            struct sockaddr_rc addr = { 0 };
            addr.rc_family = AF_BLUETOOTH;
            addr.rc_channel = (uint8_t) BLUETOOTH_PORT;
            str2ba(destination, &addr.rc_bdaddr);
            int success = connect(this->mySocket, (struct sockaddr*)&addr, sizeof(addr));
            if (success >= 0) {
                std::cout << "Bluetooth socket connection succeeded\n";
                break;
            }
            else {
                std::cout << "Bluetooth socket server refused connection. Retrying...\n";
                close(this->mySocket);
                this->mySocket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
            }
        }
        this->otherSocket = this->mySocket;
        this->otherSocketMAC = (char*)malloc(sizeof(char) * 18)
        strcpy(this->otherSocketMAC, destination);
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

BluetoothSocket BluetoothSocket::CreateBluetoothSocketByHostname(std::string hostname) {
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
}