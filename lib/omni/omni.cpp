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

#include <motor.hpp>
#include <ev3dev.h>
#include <omni.hpp>
#include <cmath>
#include <iostream>
#include <ctime>
#include <exception>
using namespace Ev3Wrap;

Omni::Omni() {
    // bind stuff according to the omni porting standard
    this->eMotor = Motor::bind(Motor::OUTPUT_A);
    this->fMotor = Motor::bind(Motor::OUTPUT_B);
    this->gMotor = Motor::bind(Motor::OUTPUT_C);
    this->hMotor = Motor::bind(Motor::OUTPUT_D);
}

Omni& Omni::controlRaw(float eSpeed, float fSpeed, float gSpeed, float hSpeed) {
    #ifdef DEBUG_MODE_ENABLED
    #define MOMS 201 // MaxOmniMotorSpeed
    if (eSpeed > MOMS || fSpeed > MOMS || gSpeed > MOMS || hSpeed > MOMS) {
        throw std::invalid_argument("e: "+std::to_string(eSpeed)+" | "
                                    "f: "+std::to_string(fSpeed)+" | "
                                    "g: "+std::to_string(gSpeed)+" | "
                                    "h: "+std::to_string(hSpeed));
    }
    #endif
    this->eMotor.runRpm(eSpeed);
    this->fMotor.runRpm(fSpeed);
    this->gMotor.runRpm(gSpeed);
    this->hMotor.runRpm(hSpeed);
    return *this;
}

