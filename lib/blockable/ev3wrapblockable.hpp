#ifndef EV3WRAPBLOCKABLE_HPP_
#define EV3WRAPBLOCKABLE_HPP_
#include <ev3dev.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <ctime>

namespace Ev3Wrap {

// blockable class
class Blockable {
    private:
        bool isBlocking;
    protected:
        void blockMilliseconds(float milliseconds) {
            if(!this->isBlocking) {return;}
            // std::chrono::milliseconds can't accept float for some reason, so we have to cast it
            std::this_thread::sleep_for(std::chrono::milliseconds((long)milliseconds));
        }
        void blockUntilStateReached(std::function<bool()> state, float loopSpeed = 5) {
            if(!this->isBlocking) {return;}
            while(true) {
                if(state()) {
                    break;
                }
                this->blockMilliseconds(loopSpeed);
            }
        }
        void blockMillisecondsAndFire(std::function<void()> function, float milliseconds) {
            if(!this->isBlocking) {return;}
            std::clock_t startTime = std::clock();
            while(true) {
                function();
                float duration = (std::clock() - startTime) / CLOCKS_PER_SEC;
                duration *= 1000;
                if(duration >= milliseconds) {
                    break;
                }
            }
            return;
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