/*
    C++ wrapper for the C++ API to the Ultrasonic Sensor of the ev3dev
    Linux kernel for the LEGO Mindstorms EV3 hardware

    Copyright (c) 2021, 2022 - Eisverygoodletter

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

#include <ev3dev.h>
#include <sstream>
#ifndef EV3WRAPUTILITIES_HPP_
#define EV3WRAPUTILITIES_HPP_
namespace Ev3Wrap {

namespace Utilities {

namespace Beeper {
    static int beepHertz = 750;
    static int beepDuration = 1000;
    static int beepRepetitions = 1;
    static int beepRepeatDelay = 500;
    static int setBeepHertz(int hz = 750) {
        Ev3Wrap::Utilities::Beeper::beepHertz = hz;
        return hz;
    }
    static int setBeepDuration(int milliseconds = 1000) {
        Ev3Wrap::Utilities::Beeper::beepDuration = milliseconds;
        return milliseconds;
    }
    static int setBeepRepetitions(int repeats = 1) {
        Ev3Wrap::Utilities::Beeper::beepRepetitions = repeats;
        return repeats;
    }
    static int setBeepRepeatDelay(int milliseconds = 500) {
        Ev3Wrap::Utilities::Beeper::beepRepeatDelay = milliseconds;
        return milliseconds;
    }
    static void beep(bool block = true) {
        std::ostringstream args;
        args << " -f " << std::to_string(beepHertz);
        args << " -l " << std::to_string(beepDuration);
        args << " -r " << std::to_string(beepRepetitions);
        args << " -d " << std::to_string(beepRepeatDelay);
        ev3dev::sound::beep(args.str(), block);
    }
}


} // namespace Utilities in namespace Ev3Wrap

} // namespace Ev3Wrap


#endif