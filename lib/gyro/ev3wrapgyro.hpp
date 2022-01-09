#include <ev3dev.h>
#ifndef EV3WRAPGYRO_HPP_
#define EV3WRAPGYRO_HPP_

namespace Ev3Wrap {

class Gyro : private ev3dev::gyro_sensor {
    public:
        static Gyro bind(ev3dev::address_type addr = ev3dev::INPUT_AUTO);
    private:
        Gyro(ev3dev::address_type addr = ev3dev::INPUT_AUTO);
};

} // namespace Ev3Wrap
#endif

/*
    
*/