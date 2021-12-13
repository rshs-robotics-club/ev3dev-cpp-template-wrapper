#include <ev3dev.h>
#ifndef EV3WRAPULTRASONIC_HPP_
#define EV3WRAPULTRASONIC_HPP_
namespace Ev3Wrap {

class UltrasonicSensor : private ev3dev::ultrasonic_sensor {
    public:
        static UltrasonicSensor bind(ev3dev::address_type addr = ev3dev::INPUT_AUTO);
        float getCentimetres() {return this->distance_centimeters();}
        bool getSensorsNearby() {return this->other_sensor_present();}
    private:
        UltrasonicSensor(ev3dev::address_type addr);
};

} // namespace Ev3Wrap
#endif