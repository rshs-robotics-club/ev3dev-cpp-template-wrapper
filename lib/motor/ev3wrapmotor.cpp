#include <ev3wrapmotor.hpp>
#include <map>
#include <string>
#include <cstring>
#include <stdexcept>

Ev3Wrap::Motor::Motor(ev3dev::address_type addr) : ev3dev::motor(addr) {
    this->defaultStopAction = MotorStopActions::brake;
    this->firingKey = 0;
};

/*
    a static constructor for the Ev3Wrap Motor class
    in code, use

    Ev3Wrap::Motor motor = Ev3Wrap::Motor::bind(ev3dev::OUTPUT_A);
    
    or something similar to construct the motor
*/

Ev3Wrap::Motor Ev3Wrap::Motor::bind(ev3dev::address_type addr) {
    Ev3Wrap::Motor retMotor = Motor(addr);
    retMotor.setDefaultStopAction(Ev3Wrap::MotorStopActions::brake);
    std::strcpy(retMotor.motorType, retMotor.driver_name().c_str());
    return retMotor;
}

// run motor forever
// takes in a float rotations per minute
Ev3Wrap::Motor& Ev3Wrap::Motor::runForever(float rpm) {
    Ev3Wrap::Motor::checkMotorLocked(this->address(), this->firingKey);
    this->runBeforeEveryFunction();
    // set the speed to tachos per minute (tachos in a rotation * rotations per minute)
    this->set_speed_sp(this->count_per_rot() * rpm / 60);
    // start running motor forever
    this->run_forever();
    return *this;
}

// run motor for a set number of Rotations
// takes in a float rotations and a float milliseconds
Ev3Wrap::Motor& Ev3Wrap::Motor::runTimed(float milliseconds, float rpm) {
    Ev3Wrap::Motor::checkMotorLocked(this->address(), this->firingKey);
    this->runBeforeEveryFunction();
    this->set_speed_sp(this->count_per_rot() * rpm / 60);
    // set speed (yes, milliseconds is directly used)
    this->set_time_sp(milliseconds);
    // start running motor timed
    this->run_timed();
    // blockable class method
    this->blockMilliseconds(milliseconds);
    return *this;
}
// takes in a float position and a float rotations per minute
Ev3Wrap::Motor& Ev3Wrap::Motor::runToAbsPos(float pos, float rpm) {
    Ev3Wrap::Motor::checkMotorLocked(this->address(), this->firingKey);
    this->runBeforeEveryFunction();
    this->set_speed_sp(this->count_per_rot() * rpm / 60);
    this->set_position_sp(this->count_per_rot() * pos);
    this->run_to_abs_pos();
    // blockable class method
    this->blockUntilStateReached([this] {
        auto s = this->state();
        // stop blocking when the motor is NOT [trying to go too fast, accelerating / decelerating, running]
        return !(
                (s.find(state_overloaded) != s.end()) || 
                (s.find(state_ramping) != s.end()) || 
                (s.find(state_running) != s.end())
        );
    });
    return *this;
}

Ev3Wrap::Motor& Ev3Wrap::Motor::runToRelPos(float relPos, float rpm) {
    Ev3Wrap::Motor::checkMotorLocked(this->address(), this->firingKey);
    this->runBeforeEveryFunction();
    this->set_speed_sp(this->count_per_rot() * rpm / 60);
    this->set_position_sp(this->count_per_rot() * relPos);
    this->run_to_rel_pos();
    // blockable class method
    this->blockUntilStateReached([this] {
        auto s = this->state();
        // stop blocking when the motor is NOT [trying to go too fast, accelerating / decelerating, running]
        return !(
                (s.find(state_overloaded) != s.end()) || 
                (s.find(state_ramping) != s.end()) || 
                (s.find(state_running) != s.end())
        );
    });
    return *this;
}

// stop and hold position (attempt to rotate back if necessary)
Ev3Wrap::Motor& Ev3Wrap::Motor::holdPosition() {
    Ev3Wrap::Motor::checkMotorLocked(this->address(), this->firingKey);
    this->runBeforeEveryFunction(); // kinda pointless here but eh
    this->setStopAction(MotorStopActions::hold);
    this->stop();
    return *this;
}

// release motor (cut electricity and allow free spin)
Ev3Wrap::Motor& Ev3Wrap::Motor::releaseMotor() {
    Ev3Wrap::Motor::checkMotorLocked(this->address(), this->firingKey);
    this->runBeforeEveryFunction(); // pointless again :*(
    this->setStopAction(MotorStopActions::coast);
    this->stop();
    return *this;
}

void Ev3Wrap::Motor::checkMotorLocked(ev3dev::address_type addr, int myKey, std::string customError) {
    if (Ev3Wrap::Motor::motorLocked[addr] != myKey) {
        throw std::invalid_argument("motor at address " + addr +" is locked but you don't have the correct key" + customError);
    }
    return;
}