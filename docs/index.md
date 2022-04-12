---
layout: default
title: Introduction
nav_order: 1
parent: Ev3Wrap
tag: "Introduction"
extra_data: 3
five: 5
verycoolitem: 5
---

<details>
<summary>Legacy build system (V1) setup tutorial</summary>

# Introduction
If you do not know what ev3dev is, go [here](https://www.ev3dev.org/).
This library is a wrapper around [ev3dev's official cpp library](https://github.com/ddemidov/ev3dev-lang-cpp). We do not guarantee that this wrapper will work.
We currently only have support for compiling on windows.
## Quick start - Installation
1. install [Docker](https://github.com/ddemidov/ev3dev-lang-cpp) and [git bash](https://git-scm.com/downloads). bash will be required to run our `*.sh` scripts for compiling, `git` will be required for downloading (and potentially contributing) to this library, and `Docker` will be required for compiling the code (in order to simulate the ev3dev-stretch OS)
2. make sure that the Docker daemon is running. (a daemon is a background task). If on windows, open up docker desktop. It should come with the Docker installation. after the "Docker Engine Initialising" screen, the docker daemon will be running
3. run `docker pull ev3dev/debian-stretch-cross` in command prompt or powershell to download the image that we will give Docker to compile our code
4. run `docker tag ev3dev/debian-stretch-cross ev3cc` to change the image's name from `ev3dev/debian-stretch-cross` to `ev3cc`. This shortens the name, and the name `ev3cc` is used in our `*.sh` scripts, so this step is NOT optional
5. using git bash, get to the folder you want the repository to be installed in. e.g. `cd C:\Users\myUsername\some_path_to_a_folder`
6. do `git clone https://github.com/rm-robotics/ev3dev-cpp-template-wrapper.git` to download/"clone" the repository onto your computer
7. inside the folder `ev3dev-cpp-template-wrapper`, create a folder named `src`, and a file named `main.cpp` inside the folder.
8. Copy and paste 
    ```cpp
    #include <iostream>
    #include <ev3wrap.h>
    int main() {
        std::cout << "Hello World!\n";
    }
    ```
    into `main.cpp` which you just created.
9.  do `cd ev3dev-cpp-template-wrapper` to move the cwd into the folder.
10. run `./scripts/compile.sh` to compile the file. Note that the docker daemon MUST be running for this bash script to work. Every time you want to compile your code in the future, run `./scripts/compile.sh`. Note that you may see a lot of `cmake` cache files appearing. That is normal and will reduce future compile times

</details>

<details>
<summary>New build system (V2 setup tutorial)</summary>

1. Familiarize yourself with the CMake build system first.(how to construct a basic cmake project)
2. Create a folder where you will store this library and your code
3. inside that folder, execute the command `git clone https://github.com/rshs-robotics-club/ev3dev-cpp-template-wrapper`. This will download the library into a folder
4. Inside that folder, execute the command `git clone https://github.com/todo-create-an-example-repo`
5. enter the example repo folder
6. edit the src files as you wish

</details>

---
# [Click here to find the Quick Start tutorials](quickstartTutorials.md)
---
# [Click here for the documentation](documentation.md)
---
