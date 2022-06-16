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
(this is updated and ready for the V2.5.0 jump)
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
   1. This part of the documentation is not finished (TODO)

---
# [Click here to find the Quick Start tutorials](quickstartTutorials.md)
---
# [Click here for the documentation](documentation.md)
---
