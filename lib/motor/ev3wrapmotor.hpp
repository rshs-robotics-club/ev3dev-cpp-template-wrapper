/*
    all standard c++ naming conventions are to be followed in this file

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

/*
    note that all motors have the nearly the same inner interface
    no separate classes for the medium and large motor are needed
*/
class Motor : private ev3dev::motor, public Blockable {
    public:
        
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
        Motor& setDefaultStopAction(MotorStopActions::StopAction stopAction) {
            this->defaultStopAction = stopAction;
            return *this;
        }
        MotorStopActions::StopAction getDefaultStopAction() {return this->defaultStopAction;}
        Motor& holdPosition();
        Motor& releaseMotor();
        using ev3dev::motor::state;

    private:
        Motor(ev3dev::address_type = ev3dev::OUTPUT_AUTO);
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