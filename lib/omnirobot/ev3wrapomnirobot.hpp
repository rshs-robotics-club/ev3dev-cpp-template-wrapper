/*
    A Controller class for Omni-directional robots coded with the C++ API to the sensors, motors, buttons, LEDs and battery of the ev3dev
    Linux kernel for the LEGO Mindstorms EV3 hardware

    Copyright (c) 2021, 2022 - Eisverygoodletter, txvvgnx

    This file is part of The Ev3dev C++ Wrapper Library.
    The Ev3dev C++ Wrapper Library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by the Free Software Foundation, 
    either version 3 of the License, or (at your option) any later version.
    The Ev3dev C++ Wrapper Library is distributed in the hope that it will be useful, 
    but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
    You should have received a copy of the GNU General Public License 
    along with The Ev3dev C++ Wrapper Library. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef EV3WRAPOMNIROBOT_HPP_
#define EV3WRAPOMNIROBOT_HPP_
#include <iostream>
#include <ev3dev.h>
#include <ev3wrapmotorpair.hpp>
#include <ev3wrapblockable.hpp>
#include <ev3wrapcompass.hpp>
#include <ev3wrapirseeker.hpp>

namespace Ev3Wrap {

class Omni : public Blockable<Omni> {
    private:
        Motor eMotor;
        Motor fMotor;
        Motor gMotor;
        Motor hMotor;
        IrSeeker& irSeeker;
        CompassSensor& compass;
    public:
        Omni(IrSeeker& irSeeker, CompassSensor& compass);
        Omni& controlRaw(float eSpeed, float fSpeed, float gSpeed, float hSpeed);
        float getMaxRpm();
        
        
};

}   // namespace Ev3Wrap

#endif

// modify this number to make the omni robot adjust for directions faster / slower
// #define OMNI_ADJUST 0.2

// namespace Ev3Wrap {
// typedef float Angle;
// /*
//     class for controlling an omni directional robot with 4 wheels.
//     assumes that the compass is facing "forwards"
//     a X motor configuration and a compass facing "fowards" will result in a 0 for motorToCompassOffset
// */
// class Omni : public Blockable<Omni> { 
//     private:
//         // left and right motors in a MotorPair. Must be in that sequence.
//         MotorPair& leftRightPair;
//         // front and back motors in a MotorPair. Must be in that sequence.
//         MotorPair& frontBackPair;
//         // the compass sensor
//         CompassSensor& compass;
//         // private constructor of the omni class. Use Ev3Wrap::Omni::CreateOmni() instead.
//         Omni(MotorPair& leftRightPair, MotorPair& frontBackPair, CompassSensor& compass, Angle motorToCompassOffset);
//         // a float to store how offset the compass is from the motor (an X shaped motor configuration is 0 degrees)
//         Angle motorToCompassOffset;
//         // calculate forwardMult and rightMult for the motor stuff
//         static std::pair<float, float> calculateMults(float x, float y, float rpm, Angle degrees);
//         // current goal the motor is going for (relative angles)
//         Angle goalDirection;
//         // current goal mults for the motors
//         std::pair<float, float> motorMults;
//         // 2 support methods for the run--- methods
//         void runForevers(float x, float y, float rpm, Angle rotation);
//         void runTimeds(float x, float y, float milliseconds, float rpm, Angle rotation);
//     public:
//         /*
//             constructor for the omni class.
//             MotorPairs need their motors in sequence with how their names are placed, (left then right) (front then back)
//             a compass is required
//             a X motor configuration and a compass facing "fowards" will result in a 0 for motorToCompassOffset.
//             in this case, the frontBackPair will refer to the top left and the front, and the bottom right as the back
//             measure an approximate value for motorToCompassOffset
            
//         */
//         static Omni CreateOmni(MotorPair& leftRightPair, MotorPair& frontBackPair, CompassSensor& compass, Angle motorToCompassOffset);
//         // fires the motors to move relative to the motors. Completely ignores compass;
//         // Blocking mode nor non-blocking mode will not make any adjustments
//         Omni& runRelativeToMotors(float x, float y, float rpm = DEFAULT_MOTOR_RPM);
//         // fires the motors to move relative to the compass.
//         // Blocking mode nor non-blocking mode will not make any adjustments
//         Omni& runRelativeToCompass(float x, float y, float rpm = DEFAULT_MOTOR_RPM);
//         // fires the motors to move relative to the "Forwards" direction given by the compass.
//         // Blocking mode nor non-blocking mode will not make any adjustments
//         Omni& runRelativeToForwards(float x, float y, float rpm = DEFAULT_MOTOR_RPM);

//         // -----------------------------------------------------------------------------------------

//         // run the motors to move relative to the motors. Completely ignores compass;
//         // Blocking mode will cause it to make adjustments for the direction
//         Omni& runRelativeToMotorsTimed(float x, float y, float milliseconds, float rpm = DEFAULT_MOTOR_RPM);
//         // run the motors to move relative to the compass.
//         // Blocking mode will cause it to make adjustments for the direction
//         Omni& runRelativeToCompassTimed(float x, float y, float milliseconds, float rpm = DEFAULT_MOTOR_RPM);
//         // run the motors to move relative to the "Forwards" direction given by the compass.
//         // blocking mode will make the robot constantly update motor speed
//         Omni& runRelativeToForwardsTimed(float x, float y, float milliseconds, float rpm = DEFAULT_MOTOR_RPM);
// };

// } // namespace Ev3Wrap



// #endif