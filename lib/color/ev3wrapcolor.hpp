#include <ev3dev.h>
#ifndef EV3WRAPCOLOR_HPP_
#define EV3WRAPCOLOR_HPP_

namespace Ev3Wrap {

enum class Color {
    NONE,
    BLACK,
    BLUE,
    GREEN,
    YELLOW,
    RED,
    WHITE,
    BROWN
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
        std::tuple<int, int, int> getRgbColor() {
            return this->raw();
        }

    private:
        ColorSensor(ev3dev::address_type addr);
};

}

#endif