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
#ifndef EV3WRAPMOTOR_HPP_
#define EV3WRAPMOTOR_HPP_
#define DEFAULT_MOTOR_RPM 50

#include <ev3dev.h>
#include <map>
#include <string>
#include <ev3wrapblockable.hpp>

namespace Ev3Wrap {

namespace MotorTypes {
    typedef char MotorType;
    constexpr MotorType mediumMotor[] = "lego-ev3-m-motor";
    constexpr MotorType largeMotor[] = "lego-ev3-l-motor";
    constexpr MotorType autoDetect[] = "REPORT-ERROR-FOR-CUSTOM-MESSAGE-IF-THIS-IS-SEEN";
}

namespace MotorStopActions {
    typedef std::string StopAction;
    static StopAction coast = "coast";
    static StopAction brake = "brake";
    static StopAction hold = "hold";
}


// predeclare classes that will use the motors
class MotorPair;
class Omni;
/*
    note that all motors have the nearly the same inner interface
    no separate classes for the medium and large motor are needed
*/
class Motor : private ev3dev::motor, public Blockable<Motor> {
    // allow motorpair and omni to access private variables of motor
    friend class Ev3Wrap::MotorPair;
    friend class Ev3Wrap::Omni;
    public:
        using ev3dev::motor::OUTPUT_A;
        using ev3dev::motor::OUTPUT_B;
        using ev3dev::motor::OUTPUT_C;
        using ev3dev::motor::OUTPUT_D;
        // type of motor - note that changing the motorType after construction will not do anything
        // this is meant to be a value to read from in debuggging
        char motorType[128];
        // constructor for the motor WITHOUT motortype specified
        // works because of ev3dev's auto detection for some components
        static Motor bind(ev3dev::address_type = ev3dev::OUTPUT_AUTO);

        // constructor for the motor with motortype specified
        // run motor for a set number of Rotations
        // takes in a float rotations and a float milliseconds
        Motor& runTimed(float milliseconds, float rpm = DEFAULT_MOTOR_RPM);
        // run motor forever
        // takes in a float rotations per minute
        Motor& runForever(float rpm = DEFAULT_MOTOR_RPM);
        // - NOTICE - MAY BE UNRELIABLE
        // takes in a float position and a float rotations per minute
        // takes in an absolute position pos in rotations and a float rpm
        Motor& runToAbsPos(float pos, float rpm = DEFAULT_MOTOR_RPM);
        // - NOTICE - MAY BE UNRELIABLE
        // float relative position and rotations per minute
        // takes in a relative position pos in rotations and a float rpm
        Motor& runToRelPos(float relPos, float rpm = DEFAULT_MOTOR_RPM);
        
        // default stop action that is updated EVERY time another run* command is done
        // a stop action may be coast, brake or hold, which define how the motors stops
        Motor& setDefaultStopAction(MotorStopActions::StopAction stopAction) {
            this->defaultStopAction = stopAction;
            return *this;
        }
        // gets the default stop action (see setDefaultStopAction for more information)
        MotorStopActions::StopAction getDefaultStopAction() {return this->defaultStopAction;}
        // stops the motor and holds it in position. Do not spam this command
        Motor& holdPosition();
        // releases the motor by cutting the electricity, allowing it to freely stop
        Motor& releaseMotor();
        // naming conventions followed
        using ev3dev::motor::state;
        // return true if motor is stalling
        bool getStalling();
        // wait until the motor stalls. This is NOT affected by blockable, and will block no matter what
        bool waitUntilStalled(float timeoutMilliseconds = 10000);


    private:
        // private constructor for the motor. Use the static bind() method instead.
        Motor(ev3dev::address_type = ev3dev::OUTPUT_AUTO);
        // defaultStopAction of this motor. Use the setDefaultStopAction and getDefaultStopAction methods instead.
        MotorStopActions::StopAction defaultStopAction;
        // please refer to setDefaultStopAction() for the actual thing you want to use
        // this is just a painful rewrite to fit naming conventions
        Motor& setStopAction(std::string stopAction) {
            this->set_stop_action(stopAction);
            return *this;
        }
        std::string getStopAction() {
            return this->stop_action();
        }
        //remember me
        void runBeforeEveryFunction() {
            this->set_stop_action(this->defaultStopAction);
        }
        
};


} //namespace Ev3wrap
#endif