#include <ev3dev.h>
#ifndef EV3WRAPIRSEEKER_HPP_
#define EV3WRAPIRSEEKER_HPP_

namespace Ev3Wrap {

class IrSeeker : private ev3dev::irseeker_sensor {
    public:
        static IrSeeker bind(ev3dev::address_type addr = ev3dev::INPUT_AUTO);
        int getDirectionAC() {return this->ac();}
        int getDirectionDC() {return this->dc();}
        std::vector<int> getAllAC(){return this->ac_all();}
        std::vector<int> getAllDC(){return this->dc_all();}
        int getACStrength() {return this->getAllAC()[this->getDirectionAC()]; }
        int getDCStrength() {return this->getAllDC()[this->getDirectionDC()]; }

        
    private:
        IrSeeker(ev3dev::address_type addr = ev3dev::INPUT_AUTO);
};

}

#endif