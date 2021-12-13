#include <ev3wrapcompass.hpp>

Ev3Wrap::CompassSensor::CompassSensor(ev3dev::address_type addr) : ev3dev::compass(addr) {};

Ev3Wrap::CompassSensor Ev3Wrap::CompassSensor::bind(ev3dev::address_type addr) {
    Ev3Wrap::CompassSensor retCompassSensor = CompassSensor(addr);
    return retCompassSensor; 
}