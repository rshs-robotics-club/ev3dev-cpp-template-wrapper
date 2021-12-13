#include <ev3dev.h>
#ifndef EV3WRAPIRSEEKER_HPP_
#define EV3WRAPIRSEEKER_HPP_

namespace Ev3Wrap {

class IrSeeker : private ev3dev::irseeker_sensor {
    public:
        static IrSeeker bind(ev3dev::address_type addr = ev3dev::INPUT_AUTO);
        float getDirectionAC() {return this->ac();}
        float getDirectionDC() {return this->dc();}
        std::tuple<int, int, int, int, int, int> getAllAC(){return this->ac_all();}
        std::tuple<int, int, int, int, int, int, int> getAllDC(){return this->dc_all();}
        // future update
        //float getLocalBearing();
        
    private:
        IrSeeker(ev3dev::address_type addr = ev3dev::INPUT_AUTO);
};

}

#endif