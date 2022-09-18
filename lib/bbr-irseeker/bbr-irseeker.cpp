#include <bbr-irseeker.hpp>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <smbus.h>
#include <iostream>
using namespace Ev3Wrap;

BBRIrSeeker BBRIrSeeker::bind(ev3dev::address_type addr) {
    return BBRIrSeeker(addr);
}
BBRIrSeeker::BBRIrSeeker(ev3dev::address_type addr) {
    this->fdPath = addr;
    this->flushPrevious();
}
int BBRIrSeeker::begin() {
    int fd = 0;
	
	// Open port for reading and writing
	if ((fd = open(this->fdPath.c_str(), O_RDWR)) < 0)
	{
		exit(2);
	}

    if (ioctl(fd, I2C_SLAVE, 0x08) < 0) 
	{					
		close(fd);
		exit(1);
	}

	return fd;
}

__s32 BBRIrSeeker::i2cReadInt(int fd, __u8 address)
{
	__s32 res = i2c_smbus_read_word_data(fd, address);
	if (0 > res) 
	{
		close(fd);
		exit(3);
	}

	// Convert result to 16 bits and swap bytes
	res = ((res<<8) & 0xFF00) | ((res>>8) & 0xFF);

	return res;
}

void BBRIrSeeker::i2cReadBlockData(int fd, __u8 address, __u8 length, __u8 *values)
{
    int potentialError = i2c_smbus_read_i2c_block_data(fd, address, length, values);
	if (0 > potentialError) 
	{
        std::string msg = "BBR IrSeeker encountered an error while reading. Error code: " + std::to_string(potentialError);
		close(fd);
		throw std::system_error(std::make_error_code(std::errc::no_such_device), msg);
	}
}

void BBRIrSeeker::getBoth(int* direction = nullptr, int* strength = nullptr) {
    int fd = this->begin();
    __u8 values[2];
    this->i2cReadBlockData(fd, 0x08, 2, values);
    close(fd);
    if (strength != nullptr) {
        *strength = (int)values[1];
    }
    if (direction != nullptr) {
        *direction = (int)values[0];
    }
    return;
}

void BBRIrSeeker::flushPrevious() {
    const int small = ((BBR_IRSEEKER_PREV_DIR > BBR_IRSEEKER_PREV_STR) * BBR_IRSEEKER_PREV_DIR) +
                      ((BBR_IRSEEKER_PREV_DIR <= BBR_IRSEEKER_PREV_STR) * BBR_IRSEEKER_PREV_STR);
    for(int i = 0; i < small; i++) {
        int dir = 0;
        int strength = 0;
        this->getBoth(&dir, &strength);
        if (BBR_IRSEEKER_PREV_DIR > i) {
            this->previousDirections[i] = dir;
        }
        if (BBR_IRSEEKER_PREV_STR > i) {
            this->previousStrengths[i] = strength;
        }
    }
    return;
}
void BBRIrSeeker::updatePrevious() {
    int dir = 0;
    int strength = 0;
    this->getBoth(&dir, &strength);
    for(int i = (BBR_IRSEEKER_PREV_DIR - 1); i > 0; i--) {
        this->previousDirections[i] = this->previousDirections[i-1];
    }
    this->previousDirections[0] = dir;
    for(int i = (BBR_IRSEEKER_PREV_STR - 1); i > 0; i--) {
        this->previousStrengths[i] = this->previousStrengths[i-1];
    }
    this->previousStrengths[0] = strength;
    return;
}
int BBRIrSeeker::getDirection(bool updatePrev) {
    if (updatePrev) {
        this->updatePrevious();
    }
    std::sort(std::begin(this->previousDirections), std::end(this->previousDirections));
    int mostFrequentDir = this->previousDirections[0];
    int frequency = 0;
    int currentlyCounting = this->previousDirections[0];
    int currentFrequency = 0;
    for(int i = 0; i < BBR_IRSEEKER_PREV_DIR; i++) {
        if (this->previousDirections[i] == currentlyCounting) {
            currentFrequency++;
        }
        else {
            if (currentFrequency > frequency) {
                mostFrequentDir = currentlyCounting;
                frequency = currentFrequency;
            }
            currentlyCounting = this->previousDirections[i];
            currentFrequency = 1;
        }
    }
    // take into account the last case
    if (currentFrequency > frequency) {
        mostFrequentDir = currentlyCounting;
    }
    return mostFrequentDir;
}

int BBRIrSeeker::getStrength(bool updatePrev) {
    if (updatePrev) {
        this->updatePrevious();
    }

    // todo
    return this->previousStrengths[0];
}

constexpr char BBRIrSeeker::INPUT_1[];
constexpr char BBRIrSeeker::INPUT_2[];
constexpr char BBRIrSeeker::INPUT_3[];
constexpr char BBRIrSeeker::INPUT_4[];
