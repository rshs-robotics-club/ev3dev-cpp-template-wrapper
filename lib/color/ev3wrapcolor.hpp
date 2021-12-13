#include <ev3dev.h>
#ifndef EV3WRAPCOLOR_HPP_
#define EV3WRAPCOLOR_HPP_

namespace Ev3Wrap {

class ColorSensor : private ev3dev::color_sensor {
    public:
        static ColorSensor bind(ev3dev::address_type addr = ev3dev::INPUT_AUTO);
        int getReflectedLightIntensity() {
            return this->reflected_light_intensity();
        }
        int getAmbientLightIntensity() {
            return this->ambient_light_intensity();
        }
        int getColor() {
             // Color detected by the sensor, categorized by overall value.
            //   - 0: No color
            //   - 1: Black
            //   - 2: Blue
            //   - 3: Green
            //   - 4: Yellow
            //   - 5: Red
            //   - 6: White
            //   - 7: Brown
            return this->color();
        }
        std::tuple<int, int, int> getRgbColor() {
            return this->raw();
        }

    private:
        ColorSensor(ev3dev::address_type addr);
};

}

#endif