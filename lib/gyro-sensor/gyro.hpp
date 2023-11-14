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
        int getAbsoluteDirection() try {
            set_mode("GYRO-ANG");
            return (value(0) % 360) - 180;
        }
        catch(...) {
            std::string msg = "Gyro Sensor failed to read absolute direction";
            throw std::system_error(std::make_error_code(std::errc::no_such_device), msg);
        }
        int getRelativeDirection() {
            return this->getAbsoluteDirection() - this->offset;
        }
        void setZero() {
            this->offset = this->getAbsoluteDirection();
        }
    private:
        GyroSensor(address_type addr = INPUT_AUTO) try : normal_sensor(addr, { ev3_gyro }) { this->offset = 0; }
        catch(...) {
            std::string msg = "Gyro Sensor failed to initialise at port " + addr;
            throw std::system_error(std::make_error_code(std::errc::no_such_device), msg);
        }
};
} // namespace Ev3Wrap

#endif