#include <ev3wrapgyro.hpp>
// the constructor for the gyro sensor
Ev3Wrap::Gyro::Gyro(ev3dev::address_type addr) : ev3dev::gyro_sensor(addr) {};
// the static constructor (public)
Ev3Wrap::Gyro Ev3Wrap::Gyro::bind(ev3dev::address_type addr) {
    Ev3Wrap::Gyro retSensor = Ev3Wrap::Gyro(addr);
    return retSensor;
}