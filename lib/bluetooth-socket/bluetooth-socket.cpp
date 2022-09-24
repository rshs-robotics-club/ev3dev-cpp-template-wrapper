#include <bluetooth-socket.hpp>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
//#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <utilities.hpp>
#include <sys/ioctl.h>
#include <poll.h>

using namespace Ev3Wrap;

BluetoothSocket BluetoothSocket::CreateBluetoothSocket(std::string dest = "", bool awokenFirst = true) {
    return BluetoothSocket(dest, awokenFirst);
}

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
        localAddr.rc_bdaddr = *BDADDR_ANY;
        localAddr.rc_channel = (uint8_t) BLUETOOTH_PORT;
        bind(this->mySocket, (struct sockaddr *)&localAddr, sizeof(localAddr));
        listen(this->mySocket, BLUETOOTH_PORT);

        this->otherSocket = accept(this->mySocket, (struct sockaddr *)&remoteAddr, &opt);
        ba2str(&remoteAddr.rc_bdaddr, this->otherSocketMAC);
        std::cout << this->otherSocketMAC << " successfully connected\n";
    }
    else {
        if (dest == "") {
            std::string msg = "destionation bluetooth MAC address was not given!\n";
            throw std::system_error(std::make_error_code(std::errc::no_such_device_or_address), msg);
        }
        struct sockaddr_rc addr = { 0 };
        char destination[18];
        strcpy(destination, dest.c_str());
        this->mySocket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
        addr.rc_family = AF_BLUETOOTH;
        addr.rc_channel = (uint8_t) BLUETOOTH_PORT;
        str2ba(destination, &addr.rc_bdaddr);
        int success = connect(this->mySocket, (struct sockaddr*)&addr, sizeof(addr));
        if (success < 0) {
            std::string msg = "client socket connection failed with code " + std::to_string(success);
            throw std::system_error(std::make_error_code(std::errc::connection_refused), msg);
        }
        this->otherSocket = this->mySocket;
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
    return (status >= 0);
}

bool BluetoothSocket::readValue(char* msg, int size) {
    //char* buffer = (char*)malloc(sizeof(*msg));
    struct pollfd *pfds;
    int nfds = 1;
    pfds = (pollfd*)calloc(nfds, sizeof(*pfds));
    if (pfds == NULL) {
        std::string msg = "Calloc failed: pfds is equal to NULL\n";
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
            std::cout << "POLLERR\n";
            return false;
        }
        if (pfds[0].revents & POLLHUP) {
            // communication ended
            this->hasDisconnected = true;
            free(pfds);
            return false;
        }
        if (pfds[0].revents & POLLIN) {
            // read values
            int bytesRead;
            bytesRead = read(this->otherSocket, msg, size);
            std::cout << bytesRead << " bytes read\n";
            if (bytesRead <= 0) {
                std::string msg = "POLLIN was detected however 0 bytes were read\n";
                throw std::system_error(std::make_error_code(std::errc::bad_message), msg);
            }
            free(pfds);
            return true;
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