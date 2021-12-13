#include <ev3wrapmotorpair.hpp>

Ev3Wrap::MotorPair::MotorPair(Ev3Wrap::Motor motor1, Ev3Wrap::Motor motor2)
{
    this->motor1 = motor1;
    this->motor2 = motor2;
}

Ev3Wrap::Motor move(float rpm)
{
    motor1.runForever(rpm);
    motor2.runForever(rpm);
}

Ev3Wrap::Motor stop()
{
    motor1.stop();
    motor2.stop();
}

Ev3Wrap::Motor Ev3Wrap::CreateMotorPair(Ev3Wrap::Motor motor1, Ev3Wrap::Motor motor2)
{
    Ev3Wrap::CreateMotorPair retMotorPair = Ev3Wrap::MotorPair(motor1, motor2);
    return retMotorPair;
}