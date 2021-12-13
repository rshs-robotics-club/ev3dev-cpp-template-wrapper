#ifndef EV3WRAPTOUCH_HPP_
#define EV3WRAPTOUCH_HPP_

#include <ev3dev.h>
#include <map>
#include <string>

namespace Ev3Wrap {

class TouchSensor : private ev3dev::touch_sensor {
    public:
        static TouchSensor bind(ev3dev::address_type = ev3dev::INPUT_AUTO);

        // Check if touch sensor is pressed
        bool isPressed() {
            return this->is_pressed();
        }
    
    private:
        TouchSensor(ev3dev::address_type = ev3dev::INPUT_AUTO);
};

}

#endif