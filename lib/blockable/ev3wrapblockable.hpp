#ifndef EV3WRAPBLOCKABLE_HPP_
#define EV3WRAPBLOCKABLE_HPP_
#include <ev3dev.h>
#include <iostream>
#include <thread>
#include <chrono>

namespace Ev3Wrap {

// blockable class
class Blockable {
    private:
        bool isBlocking;
        void block(float milliseconds) {
            if(this->isBlocking) {
                // std::chrono::milliseconds can't accept float for some reason, so we have to cast it
                std::this_thread::sleep_for(std::chrono::milliseconds((long)milliseconds));
            }
        }
    public:
        Blockable() {
            this->isBlocking = false;
        }
        bool setBlocking(bool willBlock) {
            this->isBlocking = willBlock;
            return this->isBlocking;
        }
        bool getBlocking() {
            return this->isBlocking;
        }
};


} // namespace Ev3Wrap

#endif