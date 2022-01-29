/*
    C++ wrapper for the C++ API to the Gyro of the ev3dev
    Linux kernel for the LEGO Mindstorms EV3 hardware

    Copyright (c) 2021, 2022 - Potato-eater

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

#include <ev3wrapgyro.hpp>
// the constructor for the gyro sensor
Ev3Wrap::Gyro::Gyro(ev3dev::address_type addr) : ev3dev::gyro_sensor(addr) {};
// the static constructor (public)
Ev3Wrap::Gyro Ev3Wrap::Gyro::bind(ev3dev::address_type addr) {
    Ev3Wrap::Gyro retSensor = Ev3Wrap::Gyro(addr);
    return retSensor;
}