#include <ev3dev.h>
#ifndef EV3WRAPGYRO_HPP_
#define EV3WRAPGYRO_HPP_

namespace Ev3Wrap {

class Gyro : private ev3dev::gyro_sensor {
    public:
        static Gyro bind(ev3dev::address_type addr = ev3dev::INPUT_AUTO);
        using ev3dev::gyro_sensor::angle;
        using ev3dev::gyro_sensor::rate;
        std::pair<int, int> getRateAndAngle() {
            set_mode(mode_gyro_g_a);
            return std::pair<int,int>(value(0), value(1));
        }
        int getTiltAngle() {return this->tilt_angle();}
        int getTiltRate() {return this->tilt_rate();}
    private:
        Gyro(ev3dev::address_type addr = ev3dev::INPUT_AUTO);
};

} // namespace Ev3Wrap
#endif

/*
    
*/