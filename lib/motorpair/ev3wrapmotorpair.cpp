#include <ev3wrapmotorpair.hpp>

Ev3Wrap::MotorPair::MotorPair(Ev3Wrap::Motor m1, Ev3Wrap::Motor m2) {
    this->motor1 = m1;
    this->motor2 = m2;
}

void move(float rpm) {
    Ev3Wrap::MotorPair::motor1.runForever(rpm);
    Ev3Wrap::MotorPair::motor2.runForever(rpm);
}

void stop() {
    Ev3Wrap::MotorPair::motor1.holdPosition();
    Ev3Wrap::MotorPair::motor2.holdPosition();
}

Ev3Wrap::MotorPair Ev3Wrap::MotorPair::CreateMotorPair(Ev3Wrap::Motor m1, Ev3Wrap::Motor m2) {
    Ev3Wrap::MotorPair retMotorPair = Ev3Wrap::MotorPair(m1, m2);
    return retMotorPair;
}