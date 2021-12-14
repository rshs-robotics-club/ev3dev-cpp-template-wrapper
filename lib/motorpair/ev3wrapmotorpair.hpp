#include <ev3dev.h>
#include <ev3wrapmotor.hpp>
#ifndef EV3WRAPMOTORPAIR_HPP_
#define EV3WRAPMOTORPAIR_HPP_

namespace Ev3Wrap {

class MotorPair {
    public:
        static Ev3Wrap::MotorPair CreateMotorPair(Ev3Wrap::Motor& m1, Ev3Wrap::Motor& m2);

        Ev3Wrap::Motor& motor1;
        Ev3Wrap::Motor& motor2;

        Ev3Wrap::MotorPair& runMotorsForever(float rpm1 = 50, float rpm2 = 50);
        Ev3Wrap::MotorPair& stop();

    private:
        MotorPair(Ev3Wrap::Motor& m1, Ev3Wrap::Motor& m2);
};

}
#endif