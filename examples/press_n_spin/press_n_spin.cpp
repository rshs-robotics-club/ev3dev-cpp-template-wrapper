#include <ev3wrap.hpp>

int main() {
    // construct the two buttons
    Ev3Wrap::Button myLeftButton = Ev3Wrap::Button::CreateButton(Ev3Wrap::ButtonCode::LEFT);
    Ev3Wrap::Button myRightButton = Ev3Wrap::Button::CreateButton(Ev3Wrap::ButtonCode::RIGHT);
    // construct the two motors
    Ev3Wrap::Motor myLeftMotor = Ev3Wrap::Motor::bind(Ev3Wrap::Motor::OUTPUT_A);
    Ev3Wrap::Motor myRightMotor = Ev3Wrap::Motor::bind(Ev3Wrap::Motor::OUTPUT_B);
    while (true) {
        if (myLeftButton.isPressed()) {
            myLeftMotor.runForever(50);
        }
        if (myRightButton.isPressed()) {
            myRightMotor.runForever(50);
        }
    }
    return 0;
}