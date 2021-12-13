#include <ev3wrapmotor.hpp>
#ifndef EV3WRAPMOTORPAIR_HPP_
#define EV3WRAPMOTORPAIR_HPP_

namespace EV3Wrap
{

    class MotorPair
    {
    public:
        Ev3Wrap::Motor motor1;
        Ev3Wrap::Motor motor2;

        Ev3Wrap::Motor move();
        Ev3Wrap::Motor stop();

    private:
        MotorPair(Ev3Wrap::Motor motor1, Ev3Wrap::Motor motor2);
    };

}
#endif