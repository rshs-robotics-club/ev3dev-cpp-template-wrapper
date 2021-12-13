#include <ev3dev.h>
#ifndef EV3WRAPCOMPASS_HPP_
#define EV3WRAPCOMPASS_HPP_

namespace Ev3Wrap {

class CompassSensor : private ev3dev::compass {
    public:
        static CompassSensor bind(ev3dev::address_type addr = ev3dev::INPUT_AUTO);
        int getHeadingDegrees() {
            return this->degrees();
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