/*
    C++ wrapper for the C++ API to the Touch Sensor of the ev3dev
    Linux kernel for the LEGO Mindstorms EV3 hardware

    Copyright (c) 2021, 2022 - txvvgnx

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
#ifndef EV3WRAPTOUCH_HPP_
#define EV3WRAPTOUCH_HPP_

#include <ev3dev.h>
#include <map>
#include <string>

namespace Ev3Wrap {

class TouchSensor : private ev3dev::touch_sensor {
    public:
        static TouchSensor bind(ev3dev::address_type = ev3dev::INPUT_AUTO);

        // Check if touch sensor is pressed
        bool isPressed() {
            return this->is_pressed();
        }
    
    private:
        TouchSensor(ev3dev::address_type = ev3dev::INPUT_AUTO);
};

}

#endif