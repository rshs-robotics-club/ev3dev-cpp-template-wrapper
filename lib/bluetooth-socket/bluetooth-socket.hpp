#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <utilities.hpp>
#include <sys/ioctl.h>

#ifndef EV3WRAPBLUETOOTH_SOCKET_HPP_
#define EV3WRAPBLUETOOTH_SOCKET_HPP_
#define BLUETOOTH_PORT 20
#define CHAR_ARRAY_SIZE 32
namespace Ev3Wrap {

class BluetoothSocket {
public:
    // file descriptors for sockets
    // otherSocket is used for sending and receiving messages.
    // mySocket is the one initialised for binding and listening etc.
    // they are equal if awokenFirst = false
    int mySocket, otherSocket;
    // the MAC address of the other socket. Here for debugging purposes only
    char otherSocketMAC[18];
    // send a char* buffer of data to the address.
    // It is recommended that the msg char* be of length CHAR_ARRAY_SIZE.
    // If the char* buffer size is above CHAR_ARRAY_SIZE, a custom size must be given
    bool send(char* msg, int size = CHAR_ARRAY_SIZE);
    // read the value of a socket and copy it into a char array.
    // It is recommended that the msg char* be of length CHAR_ARRAY_SIZE.
    // readValue returns false when there is no valid data to be read.
    // readValue will not throw an error if the socket is disconnected; check hasDisconnected for that
    // if the char* buffer size should NOT be under CHAR_ARRAY_SIZE (unless the sender is sending smaller messages) 
    bool readValue(char* msg, int size = CHAR_ARRAY_SIZE);
    // if the socket has been disconnected
    bool hasDisconnected;
    // if the socket is ready to attempt a reconnect
    bool readyAttemptReconnect;
    // attempt to reconnect
    // if hasDisconnected = false, this function will throw an error.
    // if readyAttemptReconnect = true, this function will not attempt to reset this->mysocket,
    // only trying to check if it can connect
    void attemptReconnect();
    // if this is true, it is a server socket which is meant to be turned on first, so that a client can connect to it
    bool awokenFirst;
    static void listDetectedDevices();
    // Create a bluetooth socket. dest (destination) is not required if it is a server socket (awokenFirst = true)
    static BluetoothSocket CreateBluetoothSocket(std::string dest = "", bool awokenFirst = true);
    // create a awokenFirst = false bluetooth socket. Searches for a list of hostnames and then connects to the one required
    static BluetoothSocket CreateBluetoothSocketByHostname(std::string hostname);
    // create a awokenFirst = true bluetooth socket. Blocks until another robot connects to the socket
    static BluetoothSocket CreateServerSocket();
    ~BluetoothSocket();
    // reconnect with the same address provided. will throw an error if hasDisconnect = false
    // if the socket is a client socket, attempts to connect to the server
private:
    // actual constructor
    BluetoothSocket(std::string dest = "", bool awokenFirst = true);
    // deactivate mySocket and otherSocket
    void fireDisconnect();

    void constructServerSocket();
    void constructClientSocket(std::string dest);
    bool pollServerConnectionReady();

    bool attemptClientConnection(std::string dest = "");
};

} // namespace Ev3Wrap

#endif