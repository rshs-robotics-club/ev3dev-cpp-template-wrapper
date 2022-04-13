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

class IrSeeker : private ev3dev::irseeker_sensor {
    public:
        using ev3dev::irseeker_sensor::INPUT_1;
        using ev3dev::irseeker_sensor::INPUT_2;
        using ev3dev::irseeker_sensor::INPUT_3;
        using ev3dev::irseeker_sensor::INPUT_4;
        static IrSeeker bind(ev3dev::address_type addr = ev3dev::INPUT_AUTO);
        int getDirectionAC() {return this->ac();}
        int getDirectionDC() {return this->dc();}
        int getDirectionACDegrees() {return (this->getDirectionAC() - 5) * 30;}
        std::vector<int> getAllAC(){return this->ac_all();}
        std::vector<int> getAllDC(){return this->dc_all();}
        int getACStrength(int IrDirection = USE_SPECIFIC_IR_DIRECTION) {
            int dir;
            if(IrDirection != FALSE) {
                dir = IrDirection;
            }
            else {
                dir = this->getDirectionAC();
            }
            // ball is not in a detected direction
            if(dir == 0) {
                return 0;
            }
            auto values = this->ac_all();
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
        int getDCStrength() {
            throw std::invalid_argument("getDCStrength IS UNTESTED AND DEPRECATED. DO NOT USE");
        }
        // returns 1 if ball is on the right of ir sensor
        //         0 if ball is in front of ir sensor
        //         -1 if ball is on the left of ir sensor
        //         -2 if ball undetected
        int getBallDirection() {
            if (this->getDirectionAC() > 5 && this->getDirectionAC() <= 9)
                return 1;
            if (this->getDirectionAC() == 5)
                return 0;
            if (this->getDirectionAC() < 5 && this->getDirectionAC() >= 1)
                return -1;

            return -2;
        }
        
    private:
        IrSeeker(ev3dev::address_type addr = ev3dev::INPUT_AUTO);
};

}

#endif