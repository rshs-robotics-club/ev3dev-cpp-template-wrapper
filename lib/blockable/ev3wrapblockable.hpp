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
template<typename blockableReturn>
class Blockable {
    private:
        bool isBlocking;
    protected:
        void blockMilliseconds(float milliseconds, std::function<void()> cleanupFunction = []{}) {
            if(!this->isBlocking) {return;}
            // std::chrono::milliseconds can't accept float for some reason, so we have to cast it
            std::this_thread::sleep_for(std::chrono::milliseconds((long)milliseconds));
            cleanupFunction();
        }
        void blockUntilStateReached(std::function<bool()> state, float loopSpeed = 5, std::function<void()> cleanupFunction = []{}) {
            if(!this->isBlocking) {return;}
            while(true) {
                if(state()) {
                    break;
                }
                this->blockMilliseconds(loopSpeed);
            }
            cleanupFunction();
        }
        void blockMillisecondsAndFire(std::function<void()> function, float milliseconds, std::function<void()> cleanupFunction = []{}) {
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
            cleanupFunction();
            return;
        }
    public:
        Blockable() {
            this->isBlocking = false;
        }
        blockableReturn& setBlocking(bool willBlock) {
            this->isBlocking = willBlock;
            return (static_cast<blockableReturn&>(*this));
        }
        bool getBlocking() {
            return this->isBlocking;
        }
        blockableReturn& wait(float milliseconds) {
            this->blockMilliseconds(milliseconds);
            return (static_cast<blockableReturn&>(*this));
        }
};


} // namespace Ev3Wrap

#endif