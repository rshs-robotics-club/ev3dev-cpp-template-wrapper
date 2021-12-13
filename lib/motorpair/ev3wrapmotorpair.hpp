#include <ev3dev.h>
#include <ev3wrapmotor.hpp>
#ifndef EV3WRAPMOTORPAIR_HPP_
#define EV3WRAPMOTORPAIR_HPP_

namespace Ev3Wrap {

class MotorPair {
    public:
        static Ev3Wrap::MotorPair CreateMotorPair(Ev3Wrap::Motor m1, Ev3Wrap::Motor m2);

        static Ev3Wrap::Motor motor1;
        static Ev3Wrap::Motor motor2;

        void move(float rpm);
        void stop();

    private:
        MotorPair(Ev3Wrap::Motor m1, Ev3Wrap::Motor m2);
};

}
#endif