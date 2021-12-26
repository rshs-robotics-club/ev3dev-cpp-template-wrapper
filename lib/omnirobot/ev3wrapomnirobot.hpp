#ifndef EV3WRAPOMNIROBOT_HPP_
#define EV3WRAPOMNIROBOT_HPP_
#include <iostream>
#include <ev3dev.h>
#include <ev3wrapmotorpair.hpp>
#include <ev3wrapblockable.hpp>
#include <ev3wrapcompass.hpp>

namespace Ev3Wrap {
typedef float Angle;
/*
    class for controlling an omni directional robot with 4 wheels.
*/
class Omni : public Blockable { 
    private:
        MotorPair& leftRightPair;
        MotorPair& frontBackPair;
        CompassSensor& compass;
        Omni(MotorPair& leftRightPair, MotorPair& frontBackPair, CompassSensor& compass);
        Angle motorToCompassOffset;
    public:
        static Omni CreateOmni(MotorPair& leftRightPair, MotorPair& frontBackPair, CompassSensor& compass);

};

} // namespace Ev3Wrap



#endif