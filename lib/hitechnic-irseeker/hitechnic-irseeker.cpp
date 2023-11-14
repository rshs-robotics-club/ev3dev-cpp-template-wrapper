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

#include <hitechnic-irseeker.hpp>
#include <ev3dev.h>
#include <iostream>
#include <system_error>
using namespace Ev3Wrap;

HiTechnicIrSeeker::HiTechnicIrSeeker(ev3dev::address_type addr) try : ev3dev::i2c_sensor(addr, { "ht-nxt-ir-seek-v2" }) {

}
catch(...) {
    std::string msg = "HiTechnic IrSeeker failed to initialise at port " + addr;
    throw std::system_error(std::make_error_code(std::errc::no_such_device), msg);
}
HiTechnicIrSeeker HiTechnicIrSeeker::bind(ev3dev::address_type addr) {
    return HiTechnicIrSeeker(addr);
}

constexpr char HiTechnicIrSeeker::INPUT_1[];
constexpr char HiTechnicIrSeeker::INPUT_2[];
constexpr char HiTechnicIrSeeker::INPUT_3[];
constexpr char HiTechnicIrSeeker::INPUT_4[];