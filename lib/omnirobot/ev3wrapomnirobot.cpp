#include <ev3wrapomnirobot.hpp>
#include <cmath>
#include <iostream>
#include <ctime>
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
}

void Omni::runForevers(float x, float y, float rpm, Angle rotation) {
    const std::pair<float, float> mults = Omni::calculateMults(x, y, rpm, rotation);
    this->leftRightPair.runMotorsForever(mults.first, -mults.first);
    this->frontBackPair.runMotorsForever(mults.second, -mults.second);
    this->goalDirection = this->compass.getRelativeDirection();
    return;
}

// define motor related functions

Omni& Omni::runRelativeToMotors(float x, float y, float rpm) {
    this->runForevers(x, y, rpm, 0);
    return *this;
}

Omni& Omni::runRelativeToCompass(float x, float y, float rpm) {
    this->runForevers(x, y, rpm, this->motorToCompassOffset);
    return *this;
}

Omni& Omni::runRelativeToForwards(float x, float y, float rpm) {
    this->runForevers(x, y, rpm, this->motorToCompassOffset + this->compass.getRelativeDirection());
    return *this;
}

void Omni::runTimeds(float x, float y, float milliseconds, float rpm, Angle rotation) {
    // calculate motor speeds
    const std::pair<float, float> mults = Omni::calculateMults(x, y, rpm, rotation);
    this->leftRightPair.runMotorsForever(mults.first, -mults.first);
    this->frontBackPair.runMotorsForever(mults.second, -mults.second);
    this->goalDirection = this->compass.getRelativeDirection();
    // store in motorMults to assist auto-adjusting in case it is blocking
    this->motorMults = mults;
    this->blockMillisecondsAndFire([this] {
        // change motor speeds depending on angle offset
        if(CompassSensor::compareAngles(this->compass.getRelativeDirection(), this->goalDirection) == 0) {return;}
        if(CompassSensor::compareAngles(this->compass.getRelativeDirection(), this->goalDirection) == -1) {
            // to the left
            this->leftRightPair.runMotorsForever(this->motorMults.first + OMNI_ADJUST, -this->motorMults.first + OMNI_ADJUST);
            this->frontBackPair.runMotorsForever(this->motorMults.second + OMNI_ADJUST, -this->motorMults.second + OMNI_ADJUST);
            this->motorMults.first += OMNI_ADJUST;
            this->motorMults.second += OMNI_ADJUST;
        }
        if(CompassSensor::compareAngles(this->compass.getRelativeDirection(), this->goalDirection) == 1) {
            // to the right
            this->leftRightPair.runMotorsForever(this->motorMults.first - OMNI_ADJUST, -this->motorMults.first - OMNI_ADJUST);
            this->frontBackPair.runMotorsForever(this->motorMults.second - OMNI_ADJUST, -this->motorMults.second - OMNI_ADJUST);
            this->motorMults.first -= OMNI_ADJUST;
            this->motorMults.second -= OMNI_ADJUST;
        }
        return;
    }, milliseconds, [this] {
        //ending function
        this->leftRightPair.stopMotors();
        this->frontBackPair.stopMotors();
    });

    if(!this->getBlocking()) {
        this->leftRightPair.runMotorsTimed(milliseconds, this->motorMults.first, -this->motorMults.first);
        this->frontBackPair.runMotorsTimed(milliseconds, this->motorMults.second, -this->motorMults.second);
    }
}

Omni& Omni::runRelativeToMotorsTimed(float x, float y, float milliseconds, float rpm) {
    this->runTimeds(x, y, milliseconds, rpm, 0);
    return *this;
}

Omni& Omni::runRelativeToCompassTimed(float x, float y, float milliseconds, float rpm) {
    this->runTimeds(x, y, milliseconds, rpm, this->motorToCompassOffset);
    return *this;
}

Omni& Omni::runRelativeToForwardsTimed(float x, float y, float milliseconds, float rpm) {
    this->runTimeds(x, y, milliseconds, rpm, this->motorToCompassOffset + this->compass.getRelativeDirection());
    return *this;
}