
### this is a quick start tutorial for using the basic two-wheeled ev3 robots, with an irseeker sensor and a compass sensor
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
        Ev3Wrap::Motor leftMotor = Ev3Wrap::Motor::bind(ev3dev::OUTPUT_A)
        // right motor is connected to ev3dev::OUTPUT_B
        Ev3Wrap::Motor rightMotor = Ev3Wrap::Motor::bind(ev3dev::OUTPUT_B)
    ```
    into the `main()` function. 
    >   Warning - if you create 2 `Ev3Wrap::Motor` objects pointing to the same output port, weird things may happen
    
    >   Tip - the motors don't necessarily have to be plugged into Port A and B. Just make sure the code corresponds to the correct ports
    
    