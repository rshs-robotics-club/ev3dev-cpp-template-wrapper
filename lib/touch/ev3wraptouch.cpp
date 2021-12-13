#include <ev3wraptouch.hpp>
#include <string>
#include <map>

Ev3Wrap::TouchSensor::TouchSensor(ev3dev::address_type addr) : ev3dev::touch_sensor(addr) {
    
}

/*
    Initalize/construct touch sensor with input port (1, 2, 3, 4) 

    Example:
    Ev3Wrap::TouchSensor touchSensor = Ev3Wrap::TouchSensor::bind(ev3dev::INPUT_1);
*/

Ev3Wrap::TouchSensor Ev3Wrap::TouchSensor::bind(ev3dev::address_type addr) { 
    Ev3Wrap::TouchSensor retTouchSensor = TouchSensor(addr);
    return retTouchSensor;
}

bool Ev3Wrap::TouchSensor::isPressed() {
    bool pressed = this->is_pressed();
    return pressed;
}