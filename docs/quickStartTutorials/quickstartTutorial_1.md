---
layout: default
title: "two wheeled robot tutorial"
parent: "Quick Start"
nav_order: 2
grand_parent: "Ev3Wrap"
---

# Quick start - 2 wheeled robot

this is a quick start tutorial for using the basic two-wheeled ev3 robots with no sensors
1.  let's start off with the basic `main.cpp` file.
    ```cpp
        #include <iostream>
        #include <ev3wrap.h>
        int main() {

            return 0;
        }
    ```
    Plug the left motor into Port `A`, and the right Motor into Port `B`
    In order for the code to recognize the motors, add
    ```cpp
        // left motor is connected to ev3dev::OUTPUT_A
        Ev3Wrap::Motor leftMotor = Ev3Wrap::Motor::bind(ev3dev::OUTPUT_A);
        // right motor is connected to ev3dev::OUTPUT_B
        Ev3Wrap::Motor rightMotor = Ev3Wrap::Motor::bind(ev3dev::OUTPUT_B);
    ```
    into the `main()` function. 
    >   Warning - if you create 2 `Ev3Wrap::Motor` objects pointing to the same output port, weird things may happen
    
    >   Tip - the motors don't necessarily have to be plugged into Port A and B. Just make sure the code corresponds to the correct ports
    
2.  Create a MotorPair containing the motors. This will help you control both motors with 1 function call
    ```cpp
        // Create the motorPair
        Ev3Wrap::MotorPair motorPair = Ev3Wrap::CreateMotorPair(leftMotor, rightMotor);
    ```
    >   Warning - the parameters should be placed in the order of (left,right)
    
    >   Tip - All Basic Input / Output classes have a static constructor `bind()`, and all "controller" classes have a static constructor `create<-insert class name here->`.

---

# ways to move the robot using `MotorPair`

---

#### Use `runMotorsForever()` to make motors run forever at a constant rpm
```cpp
// make robot move forward with a speed of 50 rpm on each motor
motorPair.runMotorsForever();
// make robot move forward with a speed of 100 rpm
motorPair.runMotorsForever(100, 100);
// make robot turn on the spot
motorPair.runMotorsForever(30, -30);
// make robot turn on the spot even faster
motorPair.runMotorsForever(60, -60);
// turn with the pivot on the left motor
motorPair.runMotorsForever(0, 100);
```
>   Warning - Calling runForever consecutively will constantly change the motor's speed

>   Warning - Only calling `runMotorsForever()` may allow the program to end before the motors even start moving. Once the program ends, the robot stops all of it's motors. Something is required to block the thread after calling `runMotorsForever()` for the motors to run for any amount of time

>   Tip - Calling `runMotorsForever()` without any parameters will make the function assume that the motors should spin at 50 rpm.

---

### Use `runMotorsTimed()` to make motors run for a set amount of milliseconds before stopping
```cpp
// make the robot move forward for 10 seconds at 50 rpm
motorPair.runMotorsTimed(10000);
// make the robot turn in a curve towards the left for 10 seconds
motorPair.runMotorsTimed(10000, 50, 100);
// make the robot move backwards for 3 seconds
motorPair.runMotorsTimed(3, -50, -50);
// make this method block the thread
motorPair.setBlocking(true);
```

>   Warning - calling any other methods of `MotorPair` before the motors stop from `runMotorsTimed()` will cancel the stopping

>   Tip - all classes inheriting from `Blockable` are non-blocking by default, meaning that after a command like this is issued, they will continue executing the next line of code. If the program ends before the command ends, the command will be cancelled.

>   Tip - use `setBlocking(true)` to make it not execute the next line of code until the motors are stopped

---

### use `stopMotors` to stop / halt the motors
```cpp
motorPair.runMotorsForever(50, 50); // make motors run forever
std::this_thread::sleep_for(std::chrono::seconds(1)) // block thread for 1 second
motorPair.stopMotors() // stop the motors
```

>   Tip - this method makes the motor exert a force to prevent it from moving.

---

### use `releaseMotors` to cut power and release the motors
```cpp
motorPair.runMotorsForever(50, 50); // make motors run forever
std::this_thread::sleep_for(std::chrono::seconds(1)) // block thread for 1 second
motorPair.releaseMotors() // release the Motors
```

>   Tip - this method makes the motor freely come to a stop, and may allow it to roll a little bit of distance before stopping

---

