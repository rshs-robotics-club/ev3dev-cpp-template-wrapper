#include <ev3wrapcompass.hpp>
#include <cstring>
Ev3Wrap::CompassSensor::CompassSensor(ev3dev::address_type addr) : ev3dev::compass(addr) {
    //degreeOffsets = {0};
    // cringe temporary fix but am too lazy
    int empty[5] = {0, 0, 0, 0, 0};
    std::memcpy(this->degreeOffsets, empty, sizeof empty);
};

Ev3Wrap::CompassSensor Ev3Wrap::CompassSensor::bind(ev3dev::address_type addr) {
    Ev3Wrap::CompassSensor retCompassSensor = CompassSensor(addr);
    return retCompassSensor; 
}