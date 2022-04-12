---
layout: default
title: "Motor tutorial"
parent: "Quick Start"
nav_order: 2
grand_parent: "Ev3Wrap-unstable-docs"
---

# This tutorial includes:
- [This tutorial includes:](#this-tutorial-includes)
  - [What is `Motor` used for?](#what-is-motor-used-for)
  - [How to bind the motor](#how-to-bind-the-motor)
        - [The bind method](#the-bind-method)
        - [Connecting 2 or more motors](#connecting-2-or-more-motors)
  - [How to run the motor at a constant speed](#how-to-run-the-motor-at-a-constant-speed)
  - [How to run the motor for a specific amount of time](#how-to-run-the-motor-for-a-specific-amount-of-time)
  - [How to stop the motor](#how-to-stop-the-motor)

---

## What is `Motor` used for?
The `Motor` class is used to represent the lego ev3 large motor and medium motor. They are represented by the same class and you do not have to specify which you are using. When measuring speed, we use rpm (rotations per minute). This ensures that there is no difference between using a large motor and a medium motor with this class. (except torque and max speed)

---

## How to bind the motor
##### The bind method
To create a **single** instance of `Motor`
Simply do 
```cpp
Ev3Wrap::Motor myMotor = Ev3Wrap::Motor::bind();
```
This will cause `myMotor` to be the first motor that the program can find connected to the ev3.

##### Connecting 2 or more motors
To create 2 or more motors, you need to specify which output ports they are connected to. These can be ports A-D
Simply do
```cpp
Ev3Wrap::Motor myMotorA = Ev3Wrap::Motor::bind(ev3dev::OUTPUT_A)
Ev3Wrap::Motor myMotorB = Ev3Wrap::Motor::bind(ev3dev::OUTPUT_B)
```
>   Warning - note that `OUTPUT_A`, `OUTPUT_B`, `OUTPUT_C` and `OUTPUT_D` are in the namespace `ev3dev` instead of `Ev3Wrap`

Specifiying which port the sensors / motors should bind to will always speed up your program. However, specifying the wrong port, using the wrong ports for i2c sensors (future tutorial), will cause a program crash.

---

## How to run the motor at a constant speed

We always measure Motor speed at rpm, rotations per minute.
>   Warning - changing the wheel size can affect the speed that a robot travels, even if the rpm is unchanged

>   Warning - a large motor may not be able to reach the same rpm as a medium motor

To make a motor spin at 50 rpm:
```cpp
myMotor.runforever(50);
```

---

## How to run the motor for a specific amount of time

In this library, we always use milliseconds as the measurement of time.
1 second = 1000 milliseconds
To make a motor spin at 50 rpm for 10 seconds
```cpp
myMotor.runTimed(10000, 50);
```
>   Warning - the timed functions in this library default to being non-blocking, meaning they will continue executing the next line of code even if you tell the motor to run for a duration. to wait for the motor to finish, do
`myMotor.setBlocking(true)`

---

## How to stop the motor

You have 2 choices:
1.  `Motor::holdPosition()`
    `holdPosition()` tells the motor to stop and resist any outside forces trying to move it. This is often preferred.
2.  `Motor::releaseMotor()`
    `releaseMotor()` tells the motor to cut electricity and come to a free stop. It still stops quick, but does a little roll before stopping

---

To find more information about the `Motor` class, click [here](../documentation/motorDocumentation.md)