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
        int getACStrength() {return this->getAllAC()[5]; }
        int getDCStrength() {return this->getAllDC()[6]; }
        // returns 1 if ball is on the right of ir sensor
        //         0 if ball is in front of ir sensor
        //         -1 if ball is on the left of ir sensor
        //         -2 if ball undetected
        int getBallDirection() {
            if (this->getDirectionAC() > 5)
                return 1;
            if (this->getDirectionAC() == 5)
                return 0;
            if (this->getDirectionAC() < 5)
                return -1;
        }
        
    private:
        IrSeeker(ev3dev::address_type addr = ev3dev::INPUT_AUTO);
};

}

#endif