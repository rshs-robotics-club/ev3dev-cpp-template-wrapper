#include <ev3wrap.hpp>

int main() {
    Ev3Wrap::UltrasonicSensor ultSensor = Ev3Wrap::UltrasonicSensor::bind(Ev3Wrap::UltrasonicSensor::INPUT_1);
    Ev3Wrap::Motor leftMotor = Ev3Wrap::Motor::bind(Ev3Wrap::Motor::OUTPUT_A);
    Ev3Wrap::Motor rightMotor = Ev3Wrap::Motor::bind(Ev3Wrap::Motor::OUTPUT_B);
    Ev3Wrap::MotorPair motorPair = Ev3Wrap::MotorPair::CreateMotorPair(leftMotor, rightMotor);
    motorPair.runMotorsForever(50);
    while (true) {
        if (ultSensor.getCentimetres() < 10) {
            break;
        }
    }
    motorPair.stopMotors();
    return 0;
}