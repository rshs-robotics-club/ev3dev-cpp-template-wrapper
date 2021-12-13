#include <ev3wrapirseeker.hpp>

Ev3Wrap::IrSeeker::IrSeeker(ev3dev::address_type addr) : ev3dev::irseeker_sensor(addr) {};

Ev3Wrap::IrSeeker Ev3Wrap::IrSeeker::bind(ev3dev::address_type addr) {
    Ev3Wrap::IrSeeker retSensor = Ev3Wrap::IrSeeker(addr);
    return retSensor;
}
/*
float Ev3Wrap::IrSeeker::getLocalBearing() {

}
*/