#include <ev3dev.h>
#include <iostream>
#include <exception>
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
        // from stackoverflow.com
        // returns 1 if otherAngle is to the right of sourceAngle,
        //         0 if the angles are identical
        //         -1 if otherAngle is to the left of sourceAngle
        static int compareAngles(float sourceAngle, float otherAngle)
        {
            // sourceAngle and otherAngle should be in the range -180 to 180
            float difference = otherAngle - sourceAngle;

            if(difference < -180.0f)
                difference += 360.0f;
            if(difference > 180.0f)
                difference -= 360.0f;

            if(difference > 0.0f)
                return 1;
            if(difference < 0.0f)
                return -1;

            return 0;
        }
        // sets the current direction as 0 degrees (in getRelativeDirection)
        CompassSensor& setZero() {
            this->degreeOffset = this->getAbsoluteDirection();
        }
        int getDegreeOffset() {
            return this->degreeOffset;
        }
        // range is different from getAbsoluteDirection, this ranges from -180 to 179
        int getRelativeDirection() {
            float ret = this->getAbsoluteDirection() - this->degreeOffset;
            if(ret >= 180) {return ret - 360;}
            if(ret < -180) {return ret + 360;}
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