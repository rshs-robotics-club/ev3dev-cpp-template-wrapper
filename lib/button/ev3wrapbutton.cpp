#include <ev3wrapbutton.hpp>

Ev3Wrap::Button::Button(int keyCode) : ev3dev::button(keyCode) {};

Ev3Wrap::Button Ev3Wrap::Button::CreateButton(ButtonCode btnCode) {
    int buttonKeyCode = static_cast<int>(btnCode);
    Ev3Wrap::Button retButton = Button(buttonKeyCode);
    retButton.setBlocking(true);
    return retButton;
}