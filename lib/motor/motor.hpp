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
#ifndef EV3WRAPMOTOR_HPP_
#define EV3WRAPMOTOR_HPP_

#include <ev3dev.h>
#include <map>
#include <string>

namespace Ev3Wrap {

namespace MotorTypes {
    typedef char MotorType;
    constexpr MotorType mediumMotor[] = "lego-ev3-m-motor";
    constexpr MotorType largeMotor[] = "lego-ev3-l-motor";
    constexpr MotorType autoDetect[] = "REPORT-ERROR-FOR-CUSTOM-MESSAGE-IF-THIS-IS-SEEN";
}

namespace MotorStopActions {
    typedef std::string StopAction;
    static StopAction coast = "coast";
    static StopAction brake = "brake";
    static StopAction hold = "hold";
}


// predeclare classes that will use the motors
class MotorPair;
class Omni;
/*
    note that all motors have the nearly the same inner interface
    no separate classes for the medium and large motor are needed
*/
using namespace ev3dev;

class Motor : protected device {
    public:
        static constexpr char OUTPUT_A[] = "ev3-ports:outA";
        static constexpr char OUTPUT_B[] = "ev3-ports:outB";
        static constexpr char OUTPUT_C[] = "ev3-ports:outC";
        static constexpr char OUTPUT_D[] = "ev3-ports:outD";
        static constexpr char STOP_BRAKE[] = "brake";
        static constexpr char STOP_COAST[] = "coast";
        static constexpr char STOP_HOLD[] = "hold";

        static Motor bind(address_type = OUTPUT_AUTO);
        void runRpm(float rpm);
        void stop(std::string stopAction = "hold");
        void initialize(ev3dev::address_type addr);
        Motor() {}; // for lazy initialization purposes, don't use normally
    private:
        Motor(ev3dev::address_type);
        bool connect(const std::map<std::string, std::set<std::string>>&) noexcept;
        int getTachosPerRotation() const { return get_attr_int("count_per_rot"); }
};

} //namespace Ev3wrap
#endif