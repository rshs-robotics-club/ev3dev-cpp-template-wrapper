/*
    C++ wrapper for the C++ API to the Motor of the ev3dev
    Linux kernel for the LEGO Mindstorms EV3 hardware

    Copyright (c) 2021, 2022 - Eisverygoodletter, Potato-eater

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

#include <motor.hpp>
#include <ev3dev.h>
#include <map>
#include <string>
#include <cstring>
#include <stdexcept>


using namespace Ev3Wrap;

constexpr char Motor::OUTPUT_A[];
constexpr char Motor::OUTPUT_B[];
constexpr char Motor::OUTPUT_C[];
constexpr char Motor::OUTPUT_D[];
constexpr char Motor::STOP_BRAKE[];
constexpr char Motor::STOP_COAST[];
constexpr char Motor::STOP_HOLD[];

Motor Motor::bind(ev3dev::address_type addr) {
    return Motor(addr);
}

void Motor::initialize(ev3dev::address_type addr) {
    connect({{ "address", { addr } }});
}

Motor::Motor(ev3dev::address_type addr) {
    this->initialize(addr);
}

bool Motor::connect(const std::map<std::string, std::set<std::string>> &match) noexcept
{
    static const std::string _strClassDir { "/sys/class" "/tacho-motor/" };
    static const std::string _strPattern  { "motor" };

    try {
        return device::connect(_strClassDir, _strPattern, match);
    } catch (...) { }

    _path.clear();

    return false;
}

void Motor::runRpm(float rpm) {
    // set the speed to tachos per minute (tachos in a rotation * rotations per minute)
    set_attr_int("speed_sp", this->getTachosPerRotation() * rpm / 60);
    // start running motor forever
    set_attr_string("command", "run-forever");
}

void Motor::stop(std::string stopAction) {
    set_attr_string("stop_action", stopAction);
    set_attr_string("command", "stop");
}