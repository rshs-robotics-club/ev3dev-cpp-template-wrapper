#ifndef EV3WRAPBUTTON_HPP_
#define EV3WRAPBUTTON_HPP_
#include <ev3dev.h>
#include <ev3wrapblockable.hpp>

namespace Ev3Wrap {

enum class ButtonCode {
    BACK = 14,
    ENTER = 28,
    UP = 103,
    LEFT = 105,
    RIGHT = 106,
    DOWN = 108
};

class Button : private ev3dev::button, public Blockable<Button> {
    public:
        static Button CreateButton(ButtonCode btnCode);
        bool isPressed() {
            return this->pressed();
        };

    private:
        Button(int keyCode);
};

}

#endif