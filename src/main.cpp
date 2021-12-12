#include <ev3wrap.hpp>
#include <iostream>
#include <chrono>
#include <thread>
int main() {
    std::cout << "Hello World!\n";
    Ev3Wrap::Motor a = Ev3Wrap::Motor::bind(ev3dev::OUTPUT_A);
    Ev3Wrap::Motor b = Ev3Wrap::Motor::bind(ev3dev::OUTPUT_B);
    a.runTimed(5000, 100);
    b.runTimed(5000, 100);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    a.holdPosition();
    b.releaseMotor();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "finished running\n";
    return 0;
}