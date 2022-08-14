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

#include <ev3dev.h>
#ifndef EV3WRAPULTRASONIC_HPP_
#define EV3WRAPULTRASONIC_HPP_
using namespace ev3dev;
namespace Ev3Wrap {

class UltrasonicSensor : private normal_sensor {
    public:
        using ev3dev::normal_sensor::INPUT_1;
        using ev3dev::normal_sensor::INPUT_2;
        using ev3dev::normal_sensor::INPUT_3;
        using ev3dev::normal_sensor::INPUT_4;
        static UltrasonicSensor bind(ev3dev::address_type addr = ev3dev::INPUT_AUTO) {
            return UltrasonicSensor(addr);
        }
        float getCentimetres() {
            set_mode("US-DIST-CM");
            return float_value(0);
        }
        bool getSensorsNearby() {
            set_mode("US-LISTEN");
            return value(0);
        }

    private:
        UltrasonicSensor(address_type addr) : normal_sensor(addr, { ev3dev::sensor::ev3_ultrasonic, ev3dev::sensor::nxt_ultrasonic }) {}
};

} // namespace Ev3Wrap
#endif