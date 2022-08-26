

#ifndef EV3WRAP_BBR_IRSEEKER_HPP_
#define EV3WRAP_BBR_IRSEEKER_HPP_

// number of old direction values to be stored
#define BBR_IRSEEKER_PREV_DIR 10
// number of old strength values to be stored
#define BBR_IRSEEKER_PREV_STR 10

#include <ev3dev.h>
namespace Ev3Wrap {

class BBRIrSeeker {
public:
    static constexpr char INPUT_1[] = "/dev/i2c-in1";
    static constexpr char INPUT_2[] = "/dev/i2c-in2";
    static constexpr char INPUT_3[] = "/dev/i2c-in3";
    static constexpr char INPUT_4[] = "/dev/i2c-in4";
    static BBRIrSeeker bind(ev3dev::address_type addr);
    int previousDirections[10];
    int previousStrengths[10];
    // fill up the old directions and strength values
    void flushPrevious();
    void updatePrevious();
    int getDirection(bool updatePrev = true);
    int getStrength(bool updatePrev = true);
private:
    int begin();
    BBRIrSeeker(ev3dev::address_type addr);
    __s32 i2cReadInt(int fd, __u8 address);
    void i2cReadBlockData(int fd, __u8 address, __u8 length, __u8 *values);
    void getBoth(int* strength, int* direction);
    char* fdPath;
};

} // namespace Ev3Wrap

#endif