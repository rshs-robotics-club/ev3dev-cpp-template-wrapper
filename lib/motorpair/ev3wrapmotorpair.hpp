/*
    A Controller class for motor pairs coded with the C++ API to the sensors, motors, buttons, LEDs and battery of the ev3dev
    Linux kernel for the LEGO Mindstorms EV3 hardware

    Copyright (c) 2021, 2022 - Eisverygoodletter, txvvgnx, NotOnAClient

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

#ifndef EV3WRAPMOTORPAIR_HPP_
#define EV3WRAPMOTORPAIR_HPP_
#include <ev3dev.h>
#include <ev3wrapmotor.hpp>
#include <ev3wrapblockable.hpp>

namespace Ev3Wrap {

class MotorPair : public Blockable<MotorPair> {
    public:
        static Ev3Wrap::MotorPair CreateMotorPair(Ev3Wrap::Motor& m1, Ev3Wrap::Motor& m2);

        Ev3Wrap::Motor& motor1;
        Ev3Wrap::Motor& motor2;

        Ev3Wrap::MotorPair& runMotorsForever(float rpm1 = 50, float rpm2 = 50);
        Ev3Wrap::MotorPair& runMotorsTimed(float milliseconds, float rpm1 = 50, float rpm2 = 50);
        Ev3Wrap::MotorPair& stopMotors();
        Ev3Wrap::MotorPair& releaseMotors();
        bool getStalling();
    private:
        MotorPair(Ev3Wrap::Motor& m1, Ev3Wrap::Motor& m2);
};

}
#endif