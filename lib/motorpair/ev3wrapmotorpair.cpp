#include <ev3wrapmotorpair.hpp>

Ev3Wrap::MotorPair::MotorPair(Ev3Wrap::Motor& m1, Ev3Wrap::Motor& m2) : motor1(m1), motor2(m2) {};

Ev3Wrap::MotorPair& Ev3Wrap::MotorPair::runMotorsForever(float rpm1, float rpm2) {
    this->motor1.runForever(rpm1);
    this->motor2.runForever(rpm2);

    return *this;
}

Ev3Wrap::MotorPair& Ev3Wrap::MotorPair::runMotorsTimed(float milliseconds, float rpm1, float rpm2) {
    this->motor1.runTimed(milliseconds, rpm1);
    this->motor2.runTimed(milliseconds, rpm2);
    this->blockMilliseconds(milliseconds);
    return *this;
}

Ev3Wrap::MotorPair& Ev3Wrap::MotorPair::stopMotors() {
    this->motor1.holdPosition();
    this->motor2.holdPosition();

    return *this;
}

Ev3Wrap::MotorPair& Ev3Wrap::MotorPair::releaseMotors() {
    this->motor1.releaseMotor();
    this->motor2.releaseMotor();

    return *this;
}

Ev3Wrap::MotorPair Ev3Wrap::MotorPair::CreateMotorPair(Ev3Wrap::Motor& m1, Ev3Wrap::Motor& m2) {
    Ev3Wrap::MotorPair retMotorPair = Ev3Wrap::MotorPair(m1, m2);
    return retMotorPair;
}

bool Ev3Wrap::MotorPair::getStalling() {
    return (this->motor1.getStalling() || this->motor2.getStalling());
}