/*
    C++ wrapper for the C++ API to the Motor of the ev3dev
    Linux kernel for the LEGO Mindstorms EV3 hardware

    Copyright (c) 2021, 2022 - Eisverygoodletter, Potato-eater

    This file is part of The Ev3dev C++ Wrapper Library.
    The Ev3dev C++ Wrapper Library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by the Free Software Foundation, 
    either version 3 of the License, or (at your option) any later version.
    The Ev3dev C++ Wrapper Library is distributed in the hope that it will be useful, 
    but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
    You should have received a copy of the GNU General Public License 
    along with The Ev3dev C++ Wrapper Library. If not, see <https://www.gnu.org/licenses/>.
*/

#include <ev3wrapmotor.hpp>
#include <map>
#include <string>
#include <cstring>
#include <stdexcept>

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
Ev3Wrap::Motor& Ev3Wrap::Motor::runForever(float rpm) {
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

bool Ev3Wrap::Motor::getStalling() {
    auto s = this->state();
    return s.find(state_stalled) != s.end();
}

Ev3Wrap::Motor& Ev3Wrap::Motor::runToRelPos(float relPos, float rpm) {
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
    this->runBeforeEveryFunction(); // kinda pointless here but eh
    if (this->stop_action() != MotorStopActions::hold)
        this->setStopAction(MotorStopActions::hold);
    // not already stopped with the state
    auto state = this->state();
    if (!(state.find(ev3dev::motor::state_holding) != state.end())) {
        this->stop();
    }
    return *this;
}

// release motor (cut electricity and allow free spin)
Ev3Wrap::Motor& Ev3Wrap::Motor::releaseMotor() {
    this->runBeforeEveryFunction(); // pointless again :*(
    if (this->getStopAction() != MotorStopActions::coast)
        this->setStopAction(MotorStopActions::coast);
    this->stop();
    return *this;
}

bool Ev3Wrap::Motor::waitUntilStalled(float timeoutMilliseconds) {
    this->blockUntilStateReached([this] {return this->getStalling();}, 5, [] {}, timeoutMilliseconds);
}

float Ev3Wrap::Motor::getMaxRpm() {
    return ((float)(this->max_speed())) * 60.0f * (1.0f / (float)(this->count_per_rot()));
}