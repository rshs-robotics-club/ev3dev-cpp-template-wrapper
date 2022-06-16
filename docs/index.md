---
layout: default
title: "Introduction"
nav_order: 1
tag: "introduction"
---
Note that this is not a completed product
# Introduction
If you do not know what ev3dev is, go [here](https://www.ev3dev.org/).
This library is a wrapper around [ev3dev's official cpp library](https://github.com/ddemidov/ev3dev-lang-cpp). We do not guarantee that this wrapper will work.
We currently only have support for compiling on windows. (MacOS support not coming soon)
## Prerequisites
- Basic Git Usage
- Basic C++ Knowledge
- An Idea of what CMake is
## Required installations
- Docker
- Git
> Note that CMake is not required to be installed on your machine, since it is actually installed within the Docker image

## Quick start - Installation
###### OS: Windows
> This installation guide assumes that you are using V2.5.0 of the library

1. Clone the repository
   1. open up command prompt
   2. open up file explorer
   3. go to the folder where you would like to install the repository
   4. Click on the folder path and copy it to the clipboard, as demonstrated like this
   ![picture of file explorer](tmp.png "TODO")
   5. Type `cd <paste clipboard file path here>`
   ![picture of command prompt](tmp.png "TODO")
   6. Hit Enter and execute the command
   7. type `git clone --recursive https://github.com/rshs-robotics-club/ev3dev-cpp-wrapper-example.git` into the command prompt
   8. Hit Enter and execute the command
   9. The repository should now be cloned into that folder.
2. Your first compilation
   1. You are now ready for compiling the library. Open the cloned repository folder with your favorite code editor. (e.g. Visual Studio Code)
   2. Turn on docker desktop. This will turn on the docker daemon (a background task) that we require for cross compiling.
   3. run `dockersetup.sh` by double clicking the file, or by running `./scripts/compile.sh` in the repository directory It should be stored inside the `scripts` folder. This will install the Docker image for the ev3 robot. 
   > Warning: the Docker image is more than 1GB and is quite large, so make sure there is space on your computer

   4. run `./scripts/compile.sh` within the repository directory. The library should now begin compiling
3. Using the library regularly
   1. The `src` folder inside the repository is where your source code should be placed.
   2. Start your first project by creating `projectName.cpp` in that folder
   3. create a `main()` function just like a normal c++ program
   4. run `./scripts/compile.sh` and the project should be compiled
   5. you can find the output `.elf` files in the `bin` folder. Note that linux (ev3dev) does not care about file extensions, but since we're using windows we make it easier for ourselves by distinguishing executables with the `.elf` extension.
   6. If you want to create more executables/projects, you can do so by creating a new `differentprojectName.cpp` file and running `./scripts/compile.sh` again. Now, you will find both `projectName.elf` and `differentprojectName.elf` in the `bin` folder. This is useful when you require quick prototyping in your project.
## Oh no! I ran into a problem
See the troubleshooting section (Not implemented yet) for solutions to common problems. If you can't find any, check [issues](https://github.com/rshs-robotics-club/ev3dev-cpp-template-wrapper/issues). If you still can't find a solution, open a new [issue](https://github.com/rshs-robotics-club/ev3dev-cpp-template-wrapper/issues) and we will try to help you.

---
# [Click here to find the Quick Start tutorials](quickstartTutorials.md)
---
# [Click here for the documentation](documentation.md)
---
