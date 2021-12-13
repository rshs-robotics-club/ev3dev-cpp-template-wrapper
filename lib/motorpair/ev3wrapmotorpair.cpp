#include <ev3wrapmotorpair.hpp>

Ev3Wrap::MotorPair::MotorPair(Ev3Wrap::Motor motor1, Ev3Wrap::Motor motor2, float rpm)
{
    this->motor1 = motor1;
    this->motor2 = motor2;
}

Ev3Wrap::Motor move(Ev3Wrap::Motor motor1, Ev3Wrap::Motor motor2, float rpm)
{
    motor1.runForever(rpm);
    motor2.runForever(rpm);
}

Ev3Wrap::Motor stop(Ev3Wrap::Motor motor1, Ev3Wrap::Motor motor2)
{
    motor1.stop();
    motor2.stop();
}