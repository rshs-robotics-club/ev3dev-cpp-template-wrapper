// macros supplied by cmakelists.txt (change in cmakelists.txt to change what components are used)
#ifndef EV3WRAP_H_
#define EV3WRAP_H_
#define DEFAULT_MOTOR_RPM 50

#include <ev3dev.h>
#include <map>
#include <string>
#include <ev3wrapblockable.hpp>
#ifdef MOTOR_USED
#include <ev3wrapmotor.hpp>
#endif
#ifdef TOUCH_USED
#include <ev3wraptouch.hpp>
#endif
#ifdef ULTRASONIC_USED
#include <ev3wrapultrasonic.hpp>
#endif
#ifdef IRSEEKER_USED
#include <ev3wrapirseeker.hpp>
#endif
#ifdef COMPASS_USED
#include <ev3wrapcompass.hpp>
#endif
#ifdef COLOR_USED
#include <ev3wrapcolor.hpp>
#endif
#ifdef MOTORPAIR_USED
#include <ev3wrapmotorpair.hpp>
#endif
#ifdef OMNIROBOT_USED
#include <ev3wrapomnirobot.hpp>
#endif
#ifdef BUTTON_USED
#include <ev3wrapbutton.hpp>
#endif
#ifndef LCD_USED
#include <ev3wraplcd.hpp>
#endif
#endif