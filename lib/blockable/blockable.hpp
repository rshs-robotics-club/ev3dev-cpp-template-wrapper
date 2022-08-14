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

// blockable class
class Blockable {
    private:
        bool isBlocking;
    protected:
        // block the thread for a number of milliseconds.
        void blockMilliseconds(float milliseconds, std::function<void()> cleanupFunction = []{}) {
            if(!this->isBlocking) {return;}
            // std::chrono::milliseconds can't accept float for some reason, so we have to cast it
            std::this_thread::sleep_for(std::chrono::milliseconds((long)milliseconds));
            cleanupFunction();
        }
        // block the thread until a state is reached, then call the cleanupFunction.
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


    public:
        Blockable() {
            this->isBlocking = false;
        }
        void setBlocking(bool willBlock) {
            this->isBlocking = willBlock;
        }
        bool getBlocking() {
            return this->isBlocking;
        }
        // wait for a number of milliseconds
        static void wait(float milliseconds) {
            std::this_thread::sleep_for(std::chrono::milliseconds((long)milliseconds));
        }
};


} // namespace Ev3Wrap

#endif