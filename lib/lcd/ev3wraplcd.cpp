#include <ev3wraplcd.hpp>

Ev3Wrap::LCD::LCD() : ev3dev::lcd() {}

Ev3Wrap::LCD Ev3Wrap::LCD::CreateLCD() {
    Ev3Wrap::LCD retLCD = LCD();
    return retLCD;
}