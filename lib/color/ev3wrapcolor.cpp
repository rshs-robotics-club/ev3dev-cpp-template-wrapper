#include <ev3wrapcolor.hpp>

Ev3Wrap::ColorSensor::ColorSensor(ev3dev::address_type addr) : ev3dev::color_sensor(addr) {}

Ev3Wrap::ColorSensor Ev3Wrap::ColorSensor::bind(ev3dev::address_type addr) {
    Ev3Wrap::ColorSensor retColorSensor = ColorSensor(addr);
    return retColorSensor;
}