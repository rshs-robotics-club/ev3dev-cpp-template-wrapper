this is unofficial (to pretty much everything) don't use this unless you know what you're doing. (we have no guarantees) 
# welcome to [ev3dev cpp template wrapper]
### this is a wrapper aimed for lego robotics on ev3dev

aimed at providing support for a few other sensors (compass and irseeker etc) and wrapping around a (slightly) modified version of `ev3dev.h` and `ev3dev.cpp` from ev3dev-lang-cpp repo

only works on windows

documentation written in the future perhaps

## how to set up docker for ev3dev compiling
1. download and install docker desktop 
2. make sure Git Bash is installed (Git Bash can be downloaded on the official Git website)
3. `"C:\Program Files\Docker\Docker\DockerCli.exe" -SwitchDaemon`
4. Wait for the Docker daemon to start (there should be a docker icon in the system tray)
5. Follow this guide (only in the "Download the ev3dev cross-compiler image" section): https://www.ev3dev.org/docs/tutorials/using-docker-to-cross-compile/

## steps to compile
1. download repository
2. open terminal
3. make sure docker is installed
4. make sure you have a folder called `src` which has a file called `main.cpp` which includes `ev3wrap.hpp`
5. `cd Downloads/ev3dev-cpp-template-wrapper`
6. `cd scripts`
7. `./compile.sh`
8. wait for stuff to happen
9. find compiled executable for the ev3 in sentFiles folder
10. edit `src/main.cpp` and write some code

## steps to run the programs on the robot
1. install FileZilla https://filezilla-project.org/download.php?type=client
2. connect to the robot, assuming ev3dev installation is vanilla the credentials are: <br />
**host**: ev3dev <br />
**username**: robot <br/>
**password**: maker <br/>
3. follow the compile guide to compile all the code 
4. using FileZilla, locate the .elf file (which is in the sentFiles folder, in the project folder)
5. drag and drop the .elf file to the robot's file system
6. make sure the file has finished transferring by checking if it is in the robot's filesystem
7. right click the .elf file and click file permissions (bottom option)
8. change the numeric value to 755 and save
9. go to the file browser on the ev3 device and run the .elf file
