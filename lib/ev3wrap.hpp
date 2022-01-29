/*
    C++ wrapper for the C++ API to the sensors, motors, buttons, LEDs and battery of the ev3dev
    Linux kernel for the LEGO Mindstorms EV3 hardware

    Copyright (c) 2021, 2022 - Eisverygoodletter, txvvgnx, Potato-eater, NotOnAClient

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


// macros supplied by cmakelists.txt (change in cmakelists.txt to change what components are used)
#ifndef EV3WRAP_H_
#define EV3WRAP_H_
#define DEFAULT_MOTOR_RPM 50

#include <ev3dev.h>
#include <map>
#include <string>
#include <ev3wrapblockable.hpp>
#ifdef MOTOR_USED
#include <ev3wrapmotor.hpp>
#endif
#ifdef TOUCH_USED
#include <ev3wraptouch.hpp>
#endif
#ifdef ULTRASONIC_USED
#include <ev3wrapultrasonic.hpp>
#endif
#ifdef IRSEEKER_USED
#include <ev3wrapirseeker.hpp>
#endif
#ifdef COMPASS_USED
#include <ev3wrapcompass.hpp>
#endif
#ifdef COLOR_USED
#include <ev3wrapcolor.hpp>
#endif
#ifdef MOTORPAIR_USED
#include <ev3wrapmotorpair.hpp>
#endif
#ifdef OMNIROBOT_USED
#include <ev3wrapomnirobot.hpp>
#endif
#ifdef BUTTON_USED
#include <ev3wrapbutton.hpp>
#endif
#ifdef LCD_USED
#include <ev3wraplcd.hpp>
#endif
#ifdef GYRO_USED
#include <ev3wrapgyro.hpp>
#endif
#endif
