#!/bin/bash
echo "wakeup"
echo $PATH
cmake ./
cmake --build ./
echo "start of program"
qemu-arm-static -L /usr/arm-linux-gnueabi/ ./sentFiles/ev3MotorTest.elf
echo "end of program"