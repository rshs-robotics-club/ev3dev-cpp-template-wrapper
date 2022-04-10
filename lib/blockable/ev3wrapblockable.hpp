/*
    C++ wrapper for the C++ API to the Brick Buttons of the ev3dev
    Linux kernel for the LEGO Mindstorms EV3 hardware

    Copyright (c) 2021, 2022 - Eisverygoodletter

    This file is part of The Ev3dev C++ Wrapper Library.
    The Ev3dev C++ Wrapper Library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by the Free Software Foundation, 
    either version 3 of the License, or (at your option) any later version.
    The Ev3dev C++ Wrapper Library is distributed in the hope that it will be useful, 
    but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
    You should have received a copy of the GNU General Public License 
    along with The Ev3dev C++ Wrapper Library. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef EV3WRAPBLOCKABLE_HPP_
#define EV3WRAPBLOCKABLE_HPP_
#include <ev3dev.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <ctime>
#include <cmath>

namespace Ev3Wrap {

// Block struct
struct Block {
    float milliseconds;
    std::function<void()> startFunction;
    std::function<void()> stopFunction;
    std::function<bool()> repeatedFunction;
    bool endState;
    float loopSpeed;
    Block& setMilliseconds(float milliseconds) {
        this->milliseconds = milliseconds;
        return *this;
    }
    Block& setStartFunction(std::function<void()> startFunction) {
        this->startFunction = startFunction;
        return *this;
    }
    Block& setStopFunction(std::function<void()> stopFunction) {
        this->stopFunction = stopFunction;
        return *this;
    }
    Block& setRepeatedFunction(std::function<bool()> repeatedFunction) {
        this->repeatedFunction = repeatedFunction;
        return *this;
    }
    Block& setLoopSpeed(float loopSpeed) {
        this->loopSpeed = loopSpeed;
        return *this;
    }
    Block() {
        milliseconds = 0;
        startFunction = nullptr;
        stopFunction = nullptr;
        repeatedFunction = nullptr;
        endState = false;
        loopSpeed = 1;
    }
};


// blockable class
template<typename blockableReturn>
class Blockable {
    private:
        bool isBlocking;
    protected:
        void processBlock(Block& block) {
            if (block.startFunction) {
                block.startFunction();
            }

            std::clock_t startTime = std::clock();
            while (true) {
                if (block.milliseconds > 0) {
                    float duration = (std::clock() - startTime) / CLOCKS_PER_SEC;
                    if (duration > block.milliseconds) {
                        break;
                    }
                }
                if (block.repeatedFunction) {
                    bool state = block.repeatedFunction();
                    if (state == block.endState) {
                        break;
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(block.loopSpeed));
            }
            if (block.stopFunction) {
                block.stopFunction();
            }
            return;
        }
        // block the thread for a number of milliseconds.
        // deprecated. Use processBlock() instead.
        void blockMilliseconds(float milliseconds, std::function<void()> cleanupFunction = []{}) {
            if(!this->isBlocking) {return;}
            // std::chrono::milliseconds can't accept float for some reason, so we have to cast it
            std::this_thread::sleep_for(std::chrono::milliseconds((long)milliseconds));
            cleanupFunction();
        }
        // block the thread until a state is reached, then call the cleanupFunction.
        // deprecated. Use processBlock() instead.
        void blockUntilStateReached(std::function<bool()> state, float loopSpeed = 5, std::function<void()> cleanupFunction = []{}, float timeoutMilliseconds = 10000) {
            if(!this->isBlocking) {return;}
            std::clock_t startTime = std::clock();
            while(true) {
                float duration = (std::clock() - startTime) / CLOCKS_PER_SEC;
                duration *= 1000;
                if (duration >= timeoutMilliseconds) {
                    break;
                }
                if(state()) {
                    break;
                }
                this->blockMilliseconds(loopSpeed);
            }
            cleanupFunction();
        }
        // block the thread and force it into a while loop where the `function` is called as fast as possible, and
        // when `milliseconds` pass, stop and call the `cleanupFunction`
        // deprecated. Use processBlock() instead.
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