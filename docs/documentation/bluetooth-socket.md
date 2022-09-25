---
title: "BluetoothSocket"
tag: "bluetooth-socket"
---

# `BluetoothSocket` class

### Description
`BluetoothSocket` is built for 1 to 1 bluetooth communication between 2 ev3 bricks. If your goal is to have multicast/broadcast related functions, either create many `BluetoothSocket`s or you're out of luck.

A `BluetoothSocket` can either be a "server socket" or a "client socket". Server sockets wait for client sockets to connect to them when created. Client sockets are initialised with a goal bluetooth `MAC` address that they attempt to connect to.

`BluetoothSocket`s can be reconnected if the connection is broken. However, the `BluetoothSocket` cannot reconnect to a different robot.

## Initialization
To initialise a Server socket, use `BluetoothSocket::CreateServerSocket()`
To initialise a Client socket, use `BluetoothSocket::CreateClientSocketByHostname(std::string hostname)` 
or 
`BluetoothSocket::CreateClientSocketByMAC(std::string MAC)`
Using the `MAC` address is recommended since no time is wasted on device detection. you can use the static function `BluetoothSocket::listDetectedDevices()` to print detected device hostnames and their `MAC` addresses.

>   Warning: normally, inquiry scans are disabled on the ev3 bluetooth adapter. to enable them, use a putty console and run `hciconfig hci0 piscan`, or put `system("hciconfig hci0 piscan")` as your first line in your `main()` function. This allows other robots to detect and connect with your robot. This property is reset every time the robot is rebooted.

## Sending data
to send data, use the `BluetoothSocket.send(char* msg, int size = CHAR_ARRAY_SIZE)` method. This takes in a `char*` buffer and the size of it. The library assumes that your buffer will be 32 bytes, (defined as `CHAR_ARRAY_SIZE`). You can have a custom size, but you will have to make sure the receiving end can handle that many bytes in 1 message.
Sending a large number of bytes increases the potential number of `write()` calls required. For simplicity, this library assumes that 1 `write()` call is enough for 1 message, hence the byte restriction at 32.

>   Tip: It is completely fine if your buffer is under 32 bytes.

>   Warning: do not do something like `mysocket.send(std::string("epic message").c_str())`. the string goes out of scope before the pointer is accessed, leading to dangling pointer problems and undefined behaviour. Properly define a `char*` buffer first.


## Reading data
to read data, use the `BluetoothSocket.readValue(char* msg, int size = CHAR_ARRAY_SIZE)` method. If you had sent over 32 bytes of data, make sure you have allocated enough memory for reading, otherwise the data will be split up and read in 2 separate occasions.

>   Warning: watch out for memory leaks! remember to `free()` your `malloc()` buffers

## Detecting disconnections
both `send` and `readValue` methods return `bool`s. These represent whether the operation succeeded or not. If they are false, it is very likely that the socket had been disconnected. Check the `BluetoothSocket.hasDisconnected` property for if it had been disconnected.

## Reconnecting after being disconnected
If the other end of the socket is disconnected for whatever reason, (such as a program crash; ended by stop button etc.) You can use `BluetoothSocket.attemptReconnect();` to try reconnect with the other robot. This is a **non-blocking** method. If it fails to reconnect, it will return `false`. Call this in your event loop or repeatedly in your program until the socket is reconnected.

>   Warning: if `BluetoothSocket.hasDisconnected` is `false` when you attempt to reconnect, it will throw an error (you're already connected!)


