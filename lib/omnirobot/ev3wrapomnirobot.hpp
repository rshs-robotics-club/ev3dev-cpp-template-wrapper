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
        OmniDirectionalRobot(MotorPair& leftRightPair, MotorPair& forwardBackPair, CompassSensor& compass);
    public:
        static OmniDirectionalRobot CreateOmniDirectionalRobot(MotorPair& leftRightPair, MotorPair& forwardBackPair, CompassSensor& compass);
    
};

} // namespace Ev3Wrap



#endif