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
        Button& blockUntilPressed() {
            this->blockUntilStateReached([this] {
                return this->pressed();
            }, 5, []{});

            return *this;
        };
        float blockUntilReleased() {
            // block until pressed
            this->blockUntilPressed();

            // capture point where button was pressed
            std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

            // block until not pressed
            this->blockUntilStateReached([this] {
                return !(this->pressed());
            }, 5, []{});

            // capture point where button was released
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

            // difference of the two points
            float difference = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

            return difference;
        };

    private:
        Button(int keyCode);
};

}

#endif