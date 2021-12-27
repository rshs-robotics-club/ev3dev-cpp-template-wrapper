#include <ev3dev.h>
#ifndef EV3WRAPCOMPASS_HPP_
#define EV3WRAPCOMPASS_HPP_

namespace Ev3Wrap {

class CompassSensor : private ev3dev::compass {
    private:
        int degreeOffset;
    public:
        static CompassSensor bind(ev3dev::address_type addr = ev3dev::INPUT_AUTO);
        // gets the absolute direction. getRelativeDirection is recommended
        int getAbsoluteDirection() {
            return this->degrees();
        }
        // sets the current direction as 0 degrees (in getRelativeDirection)
        CompassSensor& setZero() {
            this->degreeOffset = this->getAbsoluteDirection();
        }
        int getDegreeOffset() {
            return this->degreeOffset;
        }
        int getRelativeDirection() {
            float ret = this->getAbsoluteDirection() - this->degreeOffset;
            if(ret >= 360) {return ret - 360;}
            if(ret < 0) {return ret + 360;}
            return ret;
        }
        void beginCalibrate() {
            return this->begin_calibration();
        }
        void endCalibrate() {
            return this->end_calibration();
        }
        
    private:
        CompassSensor(ev3dev::address_type addr);
};

}

#endif