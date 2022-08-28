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

#include <button/button.hpp>

Ev3Wrap::Button::Button(int keyCode) : ev3dev::button(keyCode) {};

Ev3Wrap::Button Ev3Wrap::Button::CreateButton(ButtonCode btnCode) {
    int buttonKeyCode = static_cast<int>(btnCode);
    Ev3Wrap::Button retButton = Button(buttonKeyCode);
    retButton.setBlocking(true);
    return retButton;
}