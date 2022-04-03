#include <ev3wrap.hpp>

int main() {
    Ev3Wrap::Motor motorA = Ev3Wrap::Motor::bind(ev3dev::OUTPUT_A);
    motorA.setBlocking(true);
    // run at 50 rpm for 1 second (1 second == 1000 milliseconds)
    motorA.runTimed(1000, 50);
    // set blocking mode to false
    motorA.setBlocking(false);
    // tell motor to do the same thing, except it won't block the thread.
    motorA.runTimed(1000, 50);
    // don't wait for motor A to finish and immediately stop
    motorA.holdPosition();
    // end program
    return 0;
}