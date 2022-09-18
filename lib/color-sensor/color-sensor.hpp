/*
    C++ wrapper for the C++ API to the Color Sensor of the ev3dev
    Linux kernel for the LEGO Mindstorms EV3 hardware

    Copyright (c) 2021, 2022 - txxvgnx

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

#include <ev3dev.h>
#include <iostream>
#ifndef EV3WRAPCOLOR_HPP_
#define EV3WRAPCOLOR_HPP_

namespace Ev3Wrap {
using namespace ev3dev;

class ColorSensor : public normal_sensor {
    public:
        static ColorSensor bind(address_type addr = INPUT_AUTO) {
            return ColorSensor(addr);
        }
        // in the range 0-1020
        int getRed() {
            set_mode("RGB-RAW");
            return value(0);
        }
        // in the range 0-1020
        int getGreen() {
            set_mode("RGB-RAW");
            return value(1);
        }
        // in the range 0-1020
        int getBlue() {
            set_mode("RGB-RAW");
            return value(2);
        }
        // Color detected by the sensor, categorized by overall value.
        //   - 0: No color
        //   - 1: Black
        //   - 2: Blue
        //   - 3: Green
        //   - 4: Yellow
        //   - 5: Red
        //   - 6: White
        //   - 7: Brown
        int getColor() try {
            set_mode("COL-COLOR");
            return value(0);
        }
        catch(...) {
            std::string msg = "Colour sensor failed to read colour";
            throw std::system_error(std::make_error_code(std::errc::no_such_device), msg);
        }
        int getReflectedLightIntensity() {
            set_mode("COL-REFLECT");
            return value(0);
        }
        int getAmbientLightIntensity() {
            set_mode("COL-AMBIENT");
            return value(0);
        }
    private:
        ColorSensor(address_type addr = INPUT_AUTO) try : normal_sensor(addr, { ev3_color }) {

        }
        catch(...) {
            std::string msg = "Color sensor failed to initialise at port " + addr;
            throw std::system_error(std::make_error_code(std::errc::no_such_device), msg);
        }
};

}

#endif