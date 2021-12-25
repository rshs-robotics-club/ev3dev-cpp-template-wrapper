#ifndef EV3WRAPOMNIROBOT_HPP_
#define EV3WRAPOMNIROBOT_HPP_
#include <iostream>
#include <ev3dev.h>
#include <ev3wrapmotorpair.hpp>
#include <ev3wrapblockable.hpp>
#include <ev3wrapcompass.hpp>

namespace Ev3Wrap {

class OmniDirectionalRobot : public Blockable { 
    private:
        MotorPair& leftRightPair;
        MotorPair& frontBackPair;
        CompassSensor& compass;
        OmniDirectionalRobot(MotorPair& leftRightPair, MotorPair& frontBackPair, CompassSensor& compass);
    public:
        static OmniDirectionalRobot CreateOmniDirectionalRobot(MotorPair& leftRightPair, MotorPair& frontBackPair, CompassSensor& compass);
    
};

} // namespace Ev3Wrap



#endif