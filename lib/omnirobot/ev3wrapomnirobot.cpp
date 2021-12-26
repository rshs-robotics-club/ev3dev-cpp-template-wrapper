#include <ev3wrapomnirobot.hpp>
// constructor
Ev3Wrap::Omni::Omni(MotorPair& leftRightPair, MotorPair& frontBackPair, CompassSensor& compass) : 
    leftRightPair(leftRightPair), frontBackPair(frontBackPair), compass(compass) {
        std::cout << "constructing Omni\n";
};

// static public constructor
Ev3Wrap::Omni Ev3Wrap::Omni::CreateOmni(MotorPair& leftRightPair, MotorPair& frontBackPair, CompassSensor& compass) {
    Ev3Wrap::Omni retRobot = Ev3Wrap::Omni(leftRightPair, frontBackPair, compass);
    return retRobot;
};

// declare static variables
std::map<ev3dev::address_type, int> Ev3Wrap::Motor::motorLocked = {};

int Ev3Wrap::Motor::motorLockIncrement = 1;