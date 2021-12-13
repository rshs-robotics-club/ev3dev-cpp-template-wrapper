#include <ev3dev.h>
#ifndef EV3WRAPIRSEEKER_HPP_
#define EV3WRAPIRSEEKER_HPP_

namespace Ev3Wrap {

class IrSeeker : private ev3dev::irseeker_sensor {
    public:
        static IrSeeker bind(ev3dev::address_type = ev3dev::INPUT_AUTO);
    private:
        IrSeeker(ev3dev::address_type = ev3dev::INPUT_AUTO);
};

}

#endif