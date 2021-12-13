#include <ev3wrapmotorpair.hpp>

Ev3Wrap::MotorPair::MotorPair(Ev3Wrap::Motor motor1, Ev3Wrap::Motor motor2)
{
    this->motor1 = motor1;
    this->motor2 = motor2;
}

Ev3Wrap::Motor move()
{
    motor1.runForever();
    motor2.runForever();
}

Ev3Wrap::Motor stop()
{
    motor1.stop();
    motor2.stop();
}