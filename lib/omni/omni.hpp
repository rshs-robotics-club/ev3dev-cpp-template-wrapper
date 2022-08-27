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
#include <motor/motor.hpp>
namespace Ev3Wrap {

class Omni {
    private:
        Motor eMotor;
        Motor fMotor;
        Motor gMotor;
        Motor hMotor;
    public:
        Omni();
        Omni& controlRaw(float eSpeed, float fSpeed, float gSpeed, float hSpeed);
        
        
};

}   // namespace Ev3Wrap

#endif