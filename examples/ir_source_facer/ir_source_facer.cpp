#include <ev3wrap.hpp>

int main() {
    // create the irseeker instance
    Ev3Wrap::IrSeeker myIrSeeker = Ev3Wrap::IrSeeker::bind(Ev3Wrap::IrSeeker::INPUT_1);
    Ev3Wrap::Motor myLeftMotor = Ev3Wrap::Motor::bind(Ev3Wrap::Motor::OUTPUT_A);
    Ev3Wrap::Motor myRightMotor = Ev3Wrap::Motor::bind(Ev3Wrap::Motor::OUTPUT_B);
    Ev3Wrap::MotorPair myMotorPair = Ev3Wrap::MotorPair::CreateMotorPair(myLeftMotor, myRightMotor);
    while (true) {
        if (myIrSeeker.getBallDirection() < 0) {
            myMotorPair.runMotorsForever(-50, 50);
        }
        if (myIrSeeker.getBallDirection() > 0) {
            myMotorPair.runMotorsForever(50, -50);
        }
        if (myIrSeeker.getBallDirection() == 0) {
            myMotorPair.releaseMotors();
        }
    }
    return 0;
}