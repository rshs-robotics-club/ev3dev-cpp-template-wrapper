/*
    C++ wrapper for the C++ API to the Brick Buttons of the ev3dev
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

#ifndef EV3WRAPBUTTON_HPP_
#define EV3WRAPBUTTON_HPP_
#include <ev3dev.h>
#include <blockable/blockable.hpp>

namespace Ev3Wrap {

enum class ButtonCode {
    BACK = 14,
    ENTER = 28,
    UP = 103,
    LEFT = 105,
    RIGHT = 106,
    DOWN = 108
};

class Button : private ev3dev::button, public Blockable {
    public:
        static Button CreateButton(ButtonCode btnCode);
        bool isPressed() {
            return this->pressed();
        };
        void blockUntilPressed() {
            this->blockUntilStateReached([this] {
                return this->pressed();
            }, 5, []{});
        };

    private:
        Button(int keyCode);
};

}

#endif