/*
    C++ wrapper for the C++ API to the lcd of the ev3dev
    Linux kernel for the LEGO Mindstorms EV3 hardware

    Copyright (c) 2021, 2022 - txxvgnx

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

#ifndef EV3WRAPLCD_HPP_
#define EV3WRAPLCD_HPP_
#include <ev3dev.h>

namespace Ev3Wrap {

class LCD : ev3dev::lcd {
    public:
        static LCD CreateLCD();
        bool checkAvailable() {
            return this->available();
        };
        std::tuple<uint32_t, uint32_t> getResolution() {
            std::tuple<uint32_t, uint32_t> screenRes;
            screenRes = std::make_tuple(this->resolution_x(), this->resolution_y());
            return screenRes;
        };
        LCD& displayCharacter(unsigned char character) {
            this->fill(character);
            return *this;
        }

    private:
        LCD();
};

}

#endif