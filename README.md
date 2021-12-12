this is unofficial dont 
# welcome to [ev3dev cpp template wrapper]
### this is a wrapper aimed for lego robotics on ev3dev

aimed at providing support for a few other sensors (compass and irseeker etc) and wrapping around a (slightly) modified version of `ev3dev.h` and `ev3dev.cpp` from ev3dev-lang-cpp repo

only works on windows

documentation written in the future perhaps
## steps to compile
1. download repository
2. open terminal
3. make sure docker is installed
4. `cd Downloads/ev3dev-cpp-template-wrapper`
5. `cd scripts`
6. `./compile.sh`
7. wait for stuff to happen
8. find compiled executable for the ev3 in sentFiles folder
9. edit `src/main.cpp` and write some code