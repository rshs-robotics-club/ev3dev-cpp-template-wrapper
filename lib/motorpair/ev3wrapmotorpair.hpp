#ifndef EV3WRAPMOTORPAIR_HPP_
#define EV3WRAPMOTORPAIR_HPP_
#include <ev3dev.h>
#include <ev3wrapmotor.hpp>
#include <ev3wrapblockable.hpp>

namespace Ev3Wrap {

class MotorPair : public Blockable<MotorPair> {
    public:
        static Ev3Wrap::MotorPair CreateMotorPair(Ev3Wrap::Motor& m1, Ev3Wrap::Motor& m2);

        Ev3Wrap::Motor& motor1;
        Ev3Wrap::Motor& motor2;

        Ev3Wrap::MotorPair& runMotorsForever(float rpm1 = 50, float rpm2 = 50);
        Ev3Wrap::MotorPair& runMotorsTimed(float milliseconds, float rpm1 = 50, float rpm2 = 50);
        Ev3Wrap::MotorPair& stopMotors();
        Ev3Wrap::MotorPair& releaseMotors();
        Ev3Wrap::MotorPair& setMotorFiringKeys(int key = 0) {
            Motor::checkMotorLocked(motor1.address(), 0, " --- from setMotorFiringKeys");
            Motor::checkMotorLocked(motor2.address(), 0, " --- from setMotorFiringKeys");
            this->motor1.firingKey = key;
            this->motor2.firingKey = key;
        }
    private:
        MotorPair(Ev3Wrap::Motor& m1, Ev3Wrap::Motor& m2);
};

}
#endif