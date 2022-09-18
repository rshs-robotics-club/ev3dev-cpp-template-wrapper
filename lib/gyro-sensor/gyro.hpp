#include <ev3dev.h>
#ifndef EV3WRAPGYRO_HPP_
#define EV3WRAPGYRO_HPP_

namespace Ev3Wrap {
using namespace ev3dev;

class GyroSensor : public normal_sensor {
    public:
        int offset;
        static GyroSensor bind(address_type addr = INPUT_AUTO) { 
            return GyroSensor(addr);
        };
        using normal_sensor::INPUT_1;
        using normal_sensor::INPUT_2;
        using normal_sensor::INPUT_3;
        using normal_sensor::INPUT_4;
        int getAbsoluteDirection() {
            set_mode("GYRO-ANG");
            return (value(0) % 360) - 180;
        }
        int getRelativeDirection() {
            return this->getAbsoluteDirection() - this->offset;
        }
        void setZero() {
            this->offset = this->getAbsoluteDirection();
        }
    private:
        GyroSensor(address_type addr = INPUT_AUTO) : normal_sensor(addr, { ev3_gyro }) { this->offset = 0; };
};
} // namespace Ev3Wrap

#endif