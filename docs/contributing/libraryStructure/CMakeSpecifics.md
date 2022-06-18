---
layout: default
title: "CMake Specifics"
tag: "CMakeSpecifics"
---

# Step by step guide of the CMake build system of this library
### In this guide, we will open up the `CMakeLists.txt` file and examine it part by part
Lets begin with `./CMakeLists.txt`, the main file

```cmake
cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER "arm-linux-gnueabi-gcc")
set(CMAKE_CC_COMPILER "arm-linux-gnueabi-gcc")
set(CMAKE_CXX_COMPILER "arm-linux-gnueabi-g++")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)
```
Defines the system we are building on and the cmake version we are using
Compilers need to be specified so that CMake doesn't get confused in the Docker container and break, or cry out errors

---
```cmake
set(LIBNAME "ev3-cpp-template-wrapper-lib")
project(${LIBNAME} VERSION 2.0.0)
message(STATUS ${CMAKE_CXX_FLAGS})
```
Defines name of library, the version of the library (it will be changed to 2.5.0 later) and outputs the cmake flags during the build. Even though
```cmake
message(STATUS ${CMAKE_CXX_FLAGS})
```
is no longer needed, it is still useful for debugging purposes

---
```cmake
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Os)
```
Make CMake export compile commands into a file that vscode can process and use as intellisense. This is just for vscode intellisense
`add_compile_options(-Os)` tells the compiler to build the library while optimizing for size (minimising binary size) so that the robot can load the executable faster

---
```cmake
add_library(
    ${LIBNAME}
    STATIC

    lib/ev3dev.cpp
    lib/blockable/ev3wrapblockable.hpp
    lib/button/ev3wrapbutton.cpp
    lib/button/ev3wrapbutton.hpp
    ...
    lib/ev3dev.h
    lib/ev3wrap.hpp
)
```
Actually defines the library `.a` compilation goal. The files listed here contain the source code of the library.

---
```cmake
target_include_directories(
    ${LIBNAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/lib/
    ${PROJECT_SOURCE_DIR}/lib/blockable/
    ${PROJECT_SOURCE_DIR}/lib/button/
    ${PROJECT_SOURCE_DIR}/lib/color/
    ...
)
```
Tell CMake where to find the specified files from the previous part (`add_library`)

---
```cmake
set_target_properties(${LIBNAME}
                    PROPERTIES
                    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/
                    OUTPUT_NAME "ev3dev-cpp-template-wrapper"
)
```
Set the output directory and the output file name

---
```cmake
set("WRAPPER_EXAMPLES_DIR" ${PROJECT_SOURCE_DIR}/examples)
set("WRAPPER_SCRIPTS_DIR" ${PROJECT_SOURCE_DIR}/scripts)
set("WRAPPER_BIN_DIR" ${PROJECT_BINARY_DIR})
set(WRAPPER_BIN_FINISHED_DIR ${WRAPPER_BIN_DIR}/finished)
set(WRAPPER_BIN_EXAMPLES_DIR ${WRAPPER_BIN_FINISHED_DIR}/examples)
set(EVERYTHING_BUILT_TARGET "EVERYTHING_BUILT_TARGET")
set(LIB_BUILT_TARGET "LIB_BUILT_TARGET")
```
Define a list of variables that will be used later
`WRAPPER_EXAMPLES_DIR` : directory containing the example source code
`WRAPPER_SCRIPTS_DIR` : directory containing the bash scripts used for compiling
`WRAPPER_BIN_DIR` : directory containing the output binary (build folder)
`WRAPPER_BIN_FINISHED_DIR` : directory where the final finished binaries will be copied to
`WRAPPER_BIN_EXAMPLES_DIR` : directory where the finished examples will be copied to
`EVERYTHING_BUILT_TARGET`, `LIB_BUILT_TARGET` : The name of a target. This will be used later

---
```cmake
add_custom_target(
    ${EVERYTHING_BUILT_TARGET} 
    ALL
)
add_custom_target(
    ${LIB_BUILT_TARGET}
    ALL
)
```
Add the 2 targets that keep track of:
1. If everything, including the executable using the library has been built
2. If everything within the library has been built

These targets are important for when we want to measure the binary size of the library once the build is finished.

---
```cmake
add_dependencies(${EVERYTHING_BUILT_TARGET} ${LIBNAME})
add_dependencies(${LIB_BUILT_TARGET} ${EVERYTHING_BUILT_TARGET})
```
Make EVERYTHING_BUILT_TARGET depend on LIBNAME and LIB_BUILT_TARGET depend on EVERYTHING_BUILT_TARGET This is just making sure the targets make sense

---
```cmake
add_custom_command(
    TARGET ${EVERYTHING_BUILT_TARGET} POST_BUILD
    # setting up the directories
    COMMAND sudo mkdir -p ${WRAPPER_BIN_FINISHED_DIR}
    COMMAND sudo mkdir -p ${WRAPPER_BIN_EXAMPLES_DIR}
    # commands for the library itself
    COMMAND sudo cp ${WRAPPER_BIN_DIR}/libev3dev-cpp-template-wrapper.a ${WRAPPER_BIN_FINISHED_DIR}/libev3dev-cpp-template-wrapper.a
    COMMAND sudo bash ${WRAPPER_SCRIPTS_DIR}/post_build.sh "The-Ev3Wrap-library" 500 ${WRAPPER_BIN_FINISHED_DIR}/libev3dev-cpp-template-wrapper.a 50
)
```
Make it so that once everything is built, the binaries are copied to the finished folder, and `post_build.sh` is run to check its size.

---
```cmake
add_subdirectory(examples)
```
Add another CMake file stored within the `examples` folder. That other CMakeLists.txt file manages the compilation of the examples.

---

We will continue looking at `CMakeLists.txt` in the `examples` folder [here](CMakeExamples.md)