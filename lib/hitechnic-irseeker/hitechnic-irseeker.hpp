/*
    C++ wrapper for the (modified) C++ API to the Ir Seeker of the ev3dev
    Linux kernel for the LEGO Mindstorms EV3 hardware

    Copyright (c) 2021, 2022 - Eisverygoodletter, txxvgnx, Potato-eater

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
#ifndef EV3WRAPIRSEEKER_HPP_
#define EV3WRAPIRSEEKER_HPP_
#define FALSE -1000
#define USE_SPECIFIC_IR_DIRECTION FALSE
#include <exception>
#include <stdexcept>

namespace Ev3Wrap {

class HiTechnicIrSeeker : private ev3dev::i2c_sensor {
    public:
    // default address of the irseeker_sensor is 0x08
    static constexpr char INPUT_1[] = "ev3-ports:in1:i2c8";
    static constexpr char INPUT_2[] = "ev3-ports:in2:i2c8";
    static constexpr char INPUT_3[] = "ev3-ports:in3:i2c8";
    static constexpr char INPUT_4[] = "ev3-ports:in4:i2c8";
    static HiTechnicIrSeeker bind(ev3dev::address_type addr = ev3dev::INPUT_AUTO);
    int getDirection() try {
        set_mode("AC");
        return value(0);
    }
    catch(...) {
        std::string msg = "HiTechnic IrSeeker failed to get AC direction";
        throw std::system_error(std::make_error_code(std::errc::no_such_device), msg);
    }
    std::vector<int> getAll() try {
        set_mode("AC-ALL");
        return {
            value(0),
            value(1),
            value(2),
            value(3),
            value(4),
            value(5)
        };
    }
    catch(...) {
        std::string msg = "HiTechnic IrSeeker failed to get all directional strengths";
        throw std::system_error(std::make_error_code(std::errc::no_such_device), msg);
    }
    int getACStrength(int IrDirection = USE_SPECIFIC_IR_DIRECTION) try {
        int dir;
        if(IrDirection != FALSE) {
            dir = IrDirection;
        }
        else {
            dir = this->getDirection();
        }
        // ball is not in a detected direction
        if(dir == 0) {
            return 0;
        }
        std::vector<int> values = this->getAll();
        // direction is even, which means it's interpolated instead of measured from a real sensor
        if(dir % 2 == 0) {
            // take the average of the 2 closer real sensors
            // https://docs.ev3dev.org/projects/lego-linux-drivers/en/ev3dev-stretch/sensor_data.html#hitechnic-nxt-irseeker-v2
            int lowerOrderSensor = (dir / 2);
            return (values[lowerOrderSensor] + values[lowerOrderSensor + 1]) / 2;
        }
        else {
            // direction is odd
            int sensorNum = (dir + 1) / 2;
            //throw std::invalid_argument(std::to_string(sensorNum));
            return values[sensorNum];
        }
    }
    catch(...) {
        std::string msg = "HiTechnic IrSeeker failed to get AC strength";
        throw std::system_error(std::make_error_code(std::errc::no_such_device), msg);
    }
    private:
    HiTechnicIrSeeker(ev3dev::address_type addr = ev3dev::INPUT_AUTO);
};

}

#endif