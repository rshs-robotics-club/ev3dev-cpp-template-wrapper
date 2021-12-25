#include <ev3wrapomnirobot.hpp>
// constructor
Ev3Wrap::OmniDirectionalRobot::OmniDirectionalRobot(MotorPair& leftRightPair, MotorPair& frontBackPair, CompassSensor& compass) : 
    leftRightPair(leftRightPair), frontBackPair(frontBackPair), compass(compass) {
        std::cout << "constructing OmniDirectionalRobot\n";
};

// static public constructor
Ev3Wrap::OmniDirectionalRobot Ev3Wrap::OmniDirectionalRobot::CreateOmniDirectionalRobot(MotorPair& leftRightPair, MotorPair& frontBackPair, CompassSensor& compass) {
    Ev3Wrap::OmniDirectionalRobot retRobot = Ev3Wrap::OmniDirectionalRobot(leftRightPair, frontBackPair, compass);
    return retRobot;
};