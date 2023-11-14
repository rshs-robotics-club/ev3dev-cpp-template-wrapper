/*
    C++ wrapper for the (modified) C++ API to the CompassSensor of the ev3dev
    Linux kernel for the LEGO Mindstorms EV3 hardware

    Copyright (c) 2021, 2022 - Eisverygoodletter, txxvgnx

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
#include <exception>
#include <vector>
#include <system_error>
#ifndef EV3WRAPCOMPASS_HPP_
#define EV3WRAPCOMPASS_HPP_

namespace Ev3Wrap {

class HiTechnicCompass : private ev3dev::i2c_sensor {
    private:
    int degreeOffsets[5] = {0, 0, 0, 0, 0};
    HiTechnicCompass(ev3dev::address_type addr);
    public:
    static constexpr char INPUT_1[] = "ev3-ports:in1:i2c1";
    static constexpr char INPUT_2[] = "ev3-ports:in2:i2c1";
    static constexpr char INPUT_3[] = "ev3-ports:in3:i2c1";
    static constexpr char INPUT_4[] = "ev3-ports:in4:i2c1";
    static HiTechnicCompass bind(ev3dev::address_type addr = ev3dev::INPUT_AUTO);
    int getAbsoluteDirection() try {
        set_mode("COMPASS");
        return this->value(0);
    }
    catch(...) {
        std::string msg = "HiTechnic Compass failed to read absolute direction";
        throw std::system_error(std::make_error_code(std::errc::no_such_device), msg);
    }
    void beginCalibration(){ set_command("BEGIN-CAL"); }
    void endCalibration(){ set_command("END-CAL"); }

    void setZero(int key = 0) {
        this->degreeOffsets[key] = this->getAbsoluteDirection();
    }
    int getRelativeDirection(int key = 0) {
        float ret = this->getAbsoluteDirection() - this->degreeOffsets[key];
        if(ret >= 180) {return ret - 360;}
        if(ret < -180) {return ret + 360;}
        return ret;
    }
};

}

#endif