#ifndef EV3WRAPLCD_HPP_
#define EV3WRAPLCD_HPP_
#include <ev3dev.h>

namespace Ev3Wrap {

class LCD : ev3dev::lcd {
    public:
        static LCD CreateLCD();
        bool checkAvailable() {
            return this->available();
        };
        std::tuple<uint32_t, uint32_t> getResolution() {
            std::tuple<uint32_t, uint32_t> screenRes;
            screenRes = std::make_tuple(this->resolution_x(), this->resolution_y());
            return screenRes;
        };
        LCD& displayCharacter(unsigned char character) {
            this->fill(character);
            return *this;
        }

    private:
        LCD();
};

}

#endif