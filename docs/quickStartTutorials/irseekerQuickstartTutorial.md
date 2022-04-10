---
layout: default
title: irseeker tutorial
parent: Quick Start
nav_order: 3
---

# This tutorial includes:
1. how to bind the irseeker.
2. how to find if the ball is on the left or on the right side of the irseeker.
---
# Binding the irseeker:
1. put this into your `main.cpp` file.
    ```cpp
        #include <iostream>
        #include <ev3wrap.h>
        int main() {

            return 0;
        }
    ```
2. Plug the irseeker sensor into the number ports (1, 2, 3, 4)
3. In order for the code to recognize the irseeker, add:
```cpp
Ev3Wrap::IrSeeker irSeeker = Ev3Wrap::IrSeeker::bind();
// this creates an Irseeker sensor called 'irseeker'.
```
---
# finding the direction of the ball:
1. put this into your code:
```cpp
irseeker.getBallDirection()
/*
    returning 0 means that 
    the ball is in front of the sensor

    returning 1 means that 
    the ball is on the right of the sensor

    returning -1 means that 
    the ball is on the left of the sensor

    returning -2 means that
    the ball is undetected
*/
```
Example:
```cpp
// make the robot to look at the ball
while (true) {
    int ballDir = irseeker.getBallDirection();
    if (ballDir > 0) {
        // turn right
    }
    else if (ballDir < 0) {
        // turn left
    }
    else {
        // stop
    }
}
```