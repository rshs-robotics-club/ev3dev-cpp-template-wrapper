#include <ev3wrapmotor.hpp>
#include <map>
#include <string>
#include <cstring>

Ev3Wrap::Motor::Motor(ev3dev::address_type addr) : ev3dev::motor(addr) {
    this->defaultStopAction = MotorStopActions::brake;
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
Ev3Wrap::Motor Ev3Wrap::Motor::runForever(float rpm) {
    this->runBeforeEveryFunction();
    // set the speed to tachos per minute (tachos in a rotation * rotations per minute)
    this->set_speed_sp(this->count_per_rot() * rpm / 60);
    // start running motor forever
    this->run_forever();
    return *this;
}

// run motor for a set number of Rotations
// takes in a float rotations and a float milliseconds
Ev3Wrap::Motor Ev3Wrap::Motor::runTimed(float milliseconds, float rpm) {
    this->runBeforeEveryFunction();
    this->set_speed_sp(this->count_per_rot() * rpm / 60);
    // set speed (yes, milliseconds is directly used)
    this->set_time_sp(milliseconds);
    // start running motor timed
    this->run_timed();
    return *this;
}
// takes in a float position and a float rotations per minute
Ev3Wrap::Motor Ev3Wrap::Motor::runToAbsPos(float pos, float rpm) {
    this->runBeforeEveryFunction();
    this->set_speed_sp(this->count_per_rot() * rpm / 60);
    this->set_position_sp(this->count_per_rot() * pos);
    this->run_to_abs_pos();
    return *this;
}

Ev3Wrap::Motor Ev3Wrap::Motor::runToRelPos(float relPos, float rpm) {
    this->runBeforeEveryFunction();
    this->set_speed_sp(this->count_per_rot() * rpm / 60);
    this->set_position_sp(this->count_per_rot() * relPos);
    this->run_to_rel_pos();
    return *this;
}

// stop and hold position (attempt to rotate back if necessary)
Ev3Wrap::Motor Ev3Wrap::Motor::holdPosition() {
    this->runBeforeEveryFunction(); // kinda pointless here but eh
    this->setStopAction(MotorStopActions::hold);
    this->stop();
    return *this;
}

// release motor (cut electricity and allow free spin)
Ev3Wrap::Motor Ev3Wrap::Motor::releaseMotor() {
    this->runBeforeEveryFunction(); // pointless again :*(
    this->setStopAction(MotorStopActions::coast);
    this->stop();
    return *this;
}