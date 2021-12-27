#include <ev3wrapomnirobot.hpp>
#include <cmath>
#include <iostream>
using namespace Ev3Wrap;

// constructor
Omni::Omni(MotorPair& leftRightPair, MotorPair& frontBackPair, CompassSensor& compass, Angle motorToCompassOffset) : 
    leftRightPair(leftRightPair), frontBackPair(frontBackPair), compass(compass) {
    std::cout << "constructing Omni\n";
    this->motorToCompassOffset = motorToCompassOffset;
};

// static public constructor
Omni Omni::CreateOmni(MotorPair& leftRightPair, MotorPair& frontBackPair, CompassSensor& compass, Angle motorToCompassOffset) {
    Omni retRobot = Omni(leftRightPair, frontBackPair, compass, motorToCompassOffset);
    return retRobot;
};

// declare static variables
std::map<ev3dev::address_type, int> Motor::motorLocked = {};

int Motor::motorLockIncrement = 1;


std::pair<float, float> Omni::calculateMults(float x, float y, float rpm, float degrees) {
    const float fpx = rpm;
    const float fpy = -rpm;
    const float rpx = rpm;
    const float rpy = rpm;
    const float pi = atan(1) * 4;
    float newX = x * cos(degrees * pi / 180) - y * sin(degrees * pi / 180);
    float newY = x * sin(degrees * pi / 180) + y * cos(degrees * pi / 180);
    float mag = sqrt(newX * newX + newY * newY);
    newX /= mag;
    newY /= mag;
    newX *= rpm;
    newY *= rpm;
    float forwardMult = (rpm * (rpx * newY - rpy * newX)) / (rpx * fpy - fpx * rpy);
    float rightMult = (rpm * newY - fpy * forwardMult) / rpy;
    return std::make_pair(forwardMult, rightMult);
    // TODO ----------------------------------------------------------------------------------
}

// define motor related functions

Omni& Omni::runRelativeToMotors(float x, float y, float rpm) {
    const std::pair<float, float> mults = Omni::calculateMults(x, y, rpm, 0);
    this->leftRightPair.runMotorsForever(mults.first, -mults.first);
    this->frontBackPair.runMotorsForever(mults.second, -mults.second);
    return *this;
}

Omni& Omni::runRelativeToCompass(float x, float y, float rpm) {
    const std::pair<float, float> mults = Omni::calculateMults(x, y, rpm, this->motorToCompassOffset);
    this->leftRightPair.runMotorsForever(mults.first, -mults.first);
    this->frontBackPair.runMotorsForever(mults.second, -mults.second);
    return *this;
}

// TODO: define moveRelativeToForwards

// TODO: define all timed functions