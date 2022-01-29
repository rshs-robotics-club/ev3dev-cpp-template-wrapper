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

#include <ev3wrapmotorpair.hpp>

Ev3Wrap::MotorPair::MotorPair(Ev3Wrap::Motor& m1, Ev3Wrap::Motor& m2) : motor1(m1), motor2(m2) {};

Ev3Wrap::MotorPair& Ev3Wrap::MotorPair::runMotorsForever(float rpm1, float rpm2) {
    this->motor1.runForever(rpm1);
    this->motor2.runForever(rpm2);

    return *this;
}

Ev3Wrap::MotorPair& Ev3Wrap::MotorPair::runMotorsTimed(float milliseconds, float rpm1, float rpm2) {
    this->motor1.runTimed(milliseconds, rpm1);
    this->motor2.runTimed(milliseconds, rpm2);
    this->blockMilliseconds(milliseconds);
    return *this;
}

Ev3Wrap::MotorPair& Ev3Wrap::MotorPair::stopMotors() {
    this->motor1.holdPosition();
    this->motor2.holdPosition();

    return *this;
}

Ev3Wrap::MotorPair& Ev3Wrap::MotorPair::releaseMotors() {
    this->motor1.releaseMotor();
    this->motor2.releaseMotor();

    return *this;
}

Ev3Wrap::MotorPair Ev3Wrap::MotorPair::CreateMotorPair(Ev3Wrap::Motor& m1, Ev3Wrap::Motor& m2) {
    Ev3Wrap::MotorPair retMotorPair = Ev3Wrap::MotorPair(m1, m2);
    return retMotorPair;
}

bool Ev3Wrap::MotorPair::getStalling() {
    return (this->motor1.getStalling() || this->motor2.getStalling());
}