/*
    C++ wrapper for the C++ API to the Color Sensor of the ev3dev
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

#include <ev3dev.h>
#ifndef EV3WRAPCOLOR_HPP_
#define EV3WRAPCOLOR_HPP_

namespace Ev3Wrap {

enum class Color {
    NONE = 0,
    BLACK = 1,
    BLUE = 2,
    GREEN = 3,
    YELLOW = 4,
    RED = 5,
    WHITE = 6,
    BROWN = 7
};

class ColorSensor : private ev3dev::color_sensor {
    public:
        static ColorSensor bind(ev3dev::address_type addr = ev3dev::INPUT_AUTO);
        int getReflectedLightIntensity() {
            return this->reflected_light_intensity();
        }
        int getAmbientLightIntensity() {
            return this->ambient_light_intensity();
        }
        Color getColor() {
            int colorIndex = this->color();
            Color color = static_cast<Color>(colorIndex);
            return color;
        }
        std::vector<int> getRgbColor() {
            set_mode(mode_rgb_raw);
            return {value(0), value(1), value(2)};
        }

    private:
        ColorSensor(ev3dev::address_type addr);
};

}

#endif