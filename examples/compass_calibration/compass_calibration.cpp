#include <ev3wrap.hpp>
using namespace Ev3Wrap;
int main() {
    // auto bind the compass so that we don't have to customize or change it
    CompassSensor compass = CompassSensor::bind(CompassSensor::INPUT_1);
    Motor leftMotor = Motor::bind(Motor::OUTPUT_A);
    Motor rightMotor = Motor::bind(Motor::OUTPUT_B);
    MotorPair motorPair = MotorPair::CreateMotorPair(leftMotor, rightMotor);
    compass.beginCalibrate();
    motorPair.setBlocking(true);
    // values need to be changed. Refer to http://docs.ev3dev.org/projects/lego-linux-drivers/en/ev3dev-buster/sensor_data.html#ht-nxt-compass-notes
    motorPair.runMotorsTimed(20, 50, -50);
    compass.endCalibrate();
    // done
    return 0;
}