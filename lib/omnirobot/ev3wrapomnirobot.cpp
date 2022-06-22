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

#include <ev3wrapomnirobot.hpp>
#include <cmath>
#include <iostream>
#include <ctime>
#include <exception>
using namespace Ev3Wrap;

Omni::Omni(IrSeeker& irSeeker, CompassSensor& compass) : irSeeker(irSeeker), compass(compass) {
    // bind stuff according to the omni porting standard
    this->eMotor = Motor::bind(Motor::OUTPUT_A);
    this->fMotor = Motor::bind(Motor::OUTPUT_B);
    this->gMotor = Motor::bind(Motor::OUTPUT_C);
    this->hMotor = Motor::bind(Motor::OUTPUT_D);
}

Omni& Omni::controlRaw(float eSpeed, float fSpeed, float gSpeed, float hSpeed) {
    #ifdef DEBUG_MODE_ENABLED
    #define MOMS 100 // MaxOmniMotorSpeed
    if (eSpeed > MOMS || fSpeed > MOMS || gSpeed > MOMS || hSpeed > MOMS) {
        throw std::invalid_argument("e: "+std::to_string(eSpeed)+" | "
                                    "f: "+std::to_string(fSpeed)+" | "
                                    "g: "+std::to_string(gSpeed)+" | "
                                    "h: "+std::to_string(hSpeed));
    }
    #endif
    this->eMotor.runForever(eSpeed);
    this->fMotor.runForever(fSpeed);
    this->gMotor.runForever(gSpeed);
    this->hMotor.runForever(hSpeed);
    return *this;
}



// constructor
// Omni::Omni(MotorPair& leftRightPair, MotorPair& frontBackPair, CompassSensor& compass, Angle motorToCompassOffset) : 
//     leftRightPair(leftRightPair), frontBackPair(frontBackPair), compass(compass) {
//     std::cout << "constructing Omni\n";
//     this->motorToCompassOffset = motorToCompassOffset;
// };

// // static public constructor
// Omni Omni::CreateOmni(MotorPair& leftRightPair, MotorPair& frontBackPair, CompassSensor& compass, Angle motorToCompassOffset) {
//     Omni retRobot = Omni(leftRightPair, frontBackPair, compass, motorToCompassOffset);
//     return retRobot;
// };


// std::pair<float, float> Omni::calculateMults(float x, float y, float rpm, float degrees) {
//     const float fpx = rpm;
//     const float fpy = -rpm;
//     const float rpx = rpm;
//     const float rpy = rpm;
//     const float pi = atan(1) * 4;
//     float newX = x * cos(degrees * pi / 180) - y * sin(degrees * pi / 180);
//     float newY = x * sin(degrees * pi / 180) + y * cos(degrees * pi / 180);
//     float mag = sqrt(newX * newX + newY * newY);
//     newX /= mag;
//     newY /= mag;
//     newX *= rpm;
//     newY *= rpm;
//     float forwardMult = (rpm * (rpx * newY - rpy * newX)) / (rpx * fpy - fpx * rpy);
//     float rightMult = (rpm * newY - fpy * forwardMult) / rpy;
//     return std::make_pair(forwardMult, rightMult);
// }

// void Omni::runForevers(float x, float y, float rpm, Angle rotation) {
//     const std::pair<float, float> mults = Omni::calculateMults(x, y, rpm, rotation);
//     this->leftRightPair.runMotorsForever(mults.first, -mults.first);
//     this->frontBackPair.runMotorsForever(mults.second, -mults.second);
//     this->goalDirection = this->compass.getRelativeDirection();
//     return;
// }

// // define motor related functions

// Omni& Omni::runRelativeToMotors(float x, float y, float rpm) {
//     this->runForevers(x, y, rpm, 0);
//     return *this;
// }

// Omni& Omni::runRelativeToCompass(float x, float y, float rpm) {
//     this->runForevers(x, y, rpm, this->motorToCompassOffset);
//     return *this;
// }

// Omni& Omni::runRelativeToForwards(float x, float y, float rpm) {
//     this->runForevers(x, y, rpm, this->motorToCompassOffset + this->compass.getRelativeDirection());
//     return *this;
// }

// void Omni::runTimeds(float x, float y, float milliseconds, float rpm, Angle rotation) {
//     // calculate motor speeds
//     const std::pair<float, float> mults = Omni::calculateMults(x, y, rpm, rotation);
//     this->leftRightPair.runMotorsForever(mults.first, -mults.first);
//     this->frontBackPair.runMotorsForever(mults.second, -mults.second);
//     this->goalDirection = this->compass.getRelativeDirection();
//     // store in motorMults to assist auto-adjusting in case it is blocking
//     this->motorMults = mults;
//     this->blockMillisecondsAndFire([this] {
//         // change motor speeds depending on angle offset
//         if(CompassSensor::compareAngles(this->compass.getRelativeDirection(), this->goalDirection) == 0) {return;}
//         if(CompassSensor::compareAngles(this->compass.getRelativeDirection(), this->goalDirection) == -1) {
//             // to the left
//             this->leftRightPair.runMotorsForever(this->motorMults.first + OMNI_ADJUST, -this->motorMults.first + OMNI_ADJUST);
//             this->frontBackPair.runMotorsForever(this->motorMults.second + OMNI_ADJUST, -this->motorMults.second + OMNI_ADJUST);
//             this->motorMults.first += OMNI_ADJUST;
//             this->motorMults.second += OMNI_ADJUST;
//         }
//         if(CompassSensor::compareAngles(this->compass.getRelativeDirection(), this->goalDirection) == 1) {
//             // to the right
//             this->leftRightPair.runMotorsForever(this->motorMults.first - OMNI_ADJUST, -this->motorMults.first - OMNI_ADJUST);
//             this->frontBackPair.runMotorsForever(this->motorMults.second - OMNI_ADJUST, -this->motorMults.second - OMNI_ADJUST);
//             this->motorMults.first -= OMNI_ADJUST;
//             this->motorMults.second -= OMNI_ADJUST;
//         }
//         return;
//     }, milliseconds, [this] {
//         //ending function
//         this->leftRightPair.stopMotors();
//         this->frontBackPair.stopMotors();
//     });

//     if(!this->getBlocking()) {
//         this->leftRightPair.runMotorsTimed(milliseconds, this->motorMults.first, -this->motorMults.first);
//         this->frontBackPair.runMotorsTimed(milliseconds, this->motorMults.second, -this->motorMults.second);
//     }
// }

// Omni& Omni::runRelativeToMotorsTimed(float x, float y, float milliseconds, float rpm) {
//     this->runTimeds(x, y, milliseconds, rpm, 0);
//     return *this;
// }

// Omni& Omni::runRelativeToCompassTimed(float x, float y, float milliseconds, float rpm) {
//     this->runTimeds(x, y, milliseconds, rpm, this->motorToCompassOffset);
//     return *this;
// }

// Omni& Omni::runRelativeToForwardsTimed(float x, float y, float milliseconds, float rpm) {
//     this->runTimeds(x, y, milliseconds, rpm, this->motorToCompassOffset + this->compass.getRelativeDirection());
//     return *this;
// }