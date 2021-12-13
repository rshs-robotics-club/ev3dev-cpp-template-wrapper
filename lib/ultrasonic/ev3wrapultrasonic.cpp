#include <ev3wrapultrasonic.hpp>

Ev3Wrap::UltrasonicSensor::UltrasonicSensor(ev3dev::address_type addr) : ultrasonic_sensor(addr) {};

Ev3Wrap::UltrasonicSensor Ev3Wrap::UltrasonicSensor::bind(ev3dev::address_type addr) {
    Ev3Wrap::UltrasonicSensor retSensor = Ev3Wrap::UltrasonicSensor(addr);
    return retSensor;
}
