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
#ifndef EV3WRAPCOMPASS_HPP_
#define EV3WRAPCOMPASS_HPP_

namespace Ev3Wrap {

class CompassSensor : private ev3dev::compass {
    private:
        int degreeOffsets[5];
    public:
        using ev3dev::compass::INPUT_1;
        using ev3dev::compass::INPUT_2;
        using ev3dev::compass::INPUT_3;
        using ev3dev::compass::INPUT_4;
        static CompassSensor bind(ev3dev::address_type addr = ev3dev::INPUT_AUTO);
        // gets the absolute direction. getRelativeDirection is recommended
        int getAbsoluteDirection() {
            return this->degrees();
        }
        // from stackoverflow.com
        // returns 1 if otherAngle is to the right of sourceAngle,
        //         0 if the angles are identical
        //         -1 if otherAngle is to the left of sourceAngle
        static int compareAngles(float sourceAngle, float otherAngle, float tolerance = 10)
        {
            // sourceAngle and otherAngle should be in the range -180 to 180
            float difference = otherAngle - sourceAngle;

            if(difference < -180.0f)
                difference += 360.0f;
            if(difference > 180.0f)
                difference -= 360.0f;

            if(difference > tolerance)
                return 1;
            if(difference < -tolerance)
                return -1;

            return 0;
        }
        // sets the current direction as 0 degrees (in getRelativeDirection)
        CompassSensor& setZero(int key = 0) {
            this->degreeOffsets[key] = this->getAbsoluteDirection();
        }
        int getDegreeOffset(int key = 0) {
            return this->degreeOffsets[key];
        }
        // range is different from getAbsoluteDirection, this ranges from -180 to 179
        // inclusive of -180 and non inclusive of 180
        int getRelativeDirection(int key = 0) {
            float ret = this->getAbsoluteDirection() - this->degreeOffsets[key];
            if(ret >= 180) {return ret - 360;}
            if(ret < -180) {return ret + 360;}
            return ret;
        }
        void beginCalibrate() {
            return this->begin_calibration();
        }
        void endCalibrate() {
            return this->end_calibration();
        }
        
    private:
        CompassSensor(ev3dev::address_type addr);
};

}

#endif