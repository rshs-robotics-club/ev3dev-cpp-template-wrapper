#ifndef EV3WRAPMOTORPAIR_HPP_
#define EV3WRAPMOTORPAIR_HPP_
#include <ev3dev.h>
#include <ev3wrapmotor.hpp>
#include <ev3wrapblockable.hpp>

namespace Ev3Wrap {

class MotorPair : public Blockable {
    public:
        static Ev3Wrap::MotorPair CreateMotorPair(Ev3Wrap::Motor& m1, Ev3Wrap::Motor& m2);

        Ev3Wrap::Motor& motor1;
        Ev3Wrap::Motor& motor2;

        Ev3Wrap::MotorPair& runMotorsForever(float rpm1 = 50, float rpm2 = 50);
        Ev3Wrap::MotorPair& runMotorsTimed(float milliseconds, float rpm1 = 50, float rpm2 = 50);
        Ev3Wrap::MotorPair& stopMotors();
        Ev3Wrap::MotorPair& releaseMotors();

    private:
        MotorPair(Ev3Wrap::Motor& m1, Ev3Wrap::Motor& m2);
};

}
#endif