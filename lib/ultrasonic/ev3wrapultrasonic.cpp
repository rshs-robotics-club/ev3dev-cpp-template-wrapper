/*
    C++ wrapper for the C++ API to the Ultrasonic Sensor of the ev3dev
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

#include <ev3wrapultrasonic.hpp>

Ev3Wrap::UltrasonicSensor::UltrasonicSensor(ev3dev::address_type addr) : ultrasonic_sensor(addr) {};

Ev3Wrap::UltrasonicSensor Ev3Wrap::UltrasonicSensor::bind(ev3dev::address_type addr) {
    Ev3Wrap::UltrasonicSensor retSensor = Ev3Wrap::UltrasonicSensor(addr);
    return retSensor;
}