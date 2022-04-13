# 
#    A CMake file used with Docker for compiling The Ev3dev C++ Wrapper Library
#
#    Copyright (c) 2021, 2022 - Eisverygoodletter, txxvgnx
#
#    This file is part of The Ev3dev C++ Wrapper Library.
#    The Ev3dev C++ Wrapper Library is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by the Free Software Foundation, 
#    either version 3 of the License, or (at your option) any later version.
#    The Ev3dev C++ Wrapper Library is distributed in the hope that it will be useful, 
#    but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
#    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
#    You should have received a copy of the GNU General Public License 
#    along with The Ev3dev C++ Wrapper Library. If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER "arm-linux-gnueabi-gcc")
set(CMAKE_CC_COMPILER "arm-linux-gnueabi-gcc")
set(CMAKE_CXX_COMPILER "arm-linux-gnueabi-g++")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(LIBNAME "ev3-cpp-template-wrapper-lib")
project(${LIBNAME} VERSION 2.0.0)
message(STATUS ${CMAKE_CXX_FLAGS})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_compile_options(-Os)
add_library(
    ${LIBNAME} 
    STATIC

    lib/ev3dev.cpp
    
    lib/blockable/ev3wrapblockable.hpp
    lib/button/ev3wrapbutton.cpp
    lib/button/ev3wrapbutton.hpp

    lib/color/ev3wrapcolor.cpp
    lib/color/ev3wrapcolor.hpp
    
    lib/compass/ev3wrapcompass.cpp
    lib/compass/ev3wrapcompass.hpp

    lib/gyro/ev3wrapgyro.cpp
    lib/gyro/ev3wrapgyro.hpp

    lib/irseeker/ev3wrapirseeker.cpp
    lib/irseeker/ev3wrapirseeker.hpp

    lib/motor/ev3wrapmotor.cpp
    lib/motor/ev3wrapmotor.hpp

    lib/motorpair/ev3wrapmotorpair.cpp
    lib/motorpair/ev3wrapmotorpair.hpp

    lib/omnirobot/ev3wrapomnirobot.cpp
    lib/omnirobot/ev3wrapomnirobot.hpp

    lib/touch/ev3wraptouch.cpp
    lib/touch/ev3wraptouch.hpp

    lib/ultrasonic/ev3wrapultrasonic.cpp
    lib/ultrasonic/ev3wrapultrasonic.hpp

    lib/utilities/ev3wraputilities.hpp

    lib/ev3dev.h

    lib/ev3wrap.hpp
)
target_include_directories(
    ${LIBNAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/lib/
    ${PROJECT_SOURCE_DIR}/lib/blockable/
    ${PROJECT_SOURCE_DIR}/lib/button/
    ${PROJECT_SOURCE_DIR}/lib/color/
    ${PROJECT_SOURCE_DIR}/lib/compass/
    ${PROJECT_SOURCE_DIR}/lib/gyro/
    ${PROJECT_SOURCE_DIR}/lib/irseeker/
    ${PROJECT_SOURCE_DIR}/lib/motor/
    ${PROJECT_SOURCE_DIR}/lib/motorpair/
    ${PROJECT_SOURCE_DIR}/lib/omnirobot/
    ${PROJECT_SOURCE_DIR}/lib/touch/
    ${PROJECT_SOURCE_DIR}/lib/ultrasonic/
    ${PROJECT_SOURCE_DIR}/lib/utilities/
)

set_target_properties(${LIBNAME}
                    PROPERTIES
                    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/
                    OUTPUT_NAME "ev3dev-cpp-template-wrapper"
)

set("WRAPPER_EXAMPLES_DIR" ${PROJECT_SOURCE_DIR}/examples)
set("WRAPPER_SCRIPTS_DIR" ${PROJECT_SOURCE_DIR}/scripts)
set("WRAPPER_BIN_DIR" ${PROJECT_BINARY_DIR})
set(WRAPPER_BIN_FINISHED_DIR ${WRAPPER_BIN_DIR}/finished)
set(WRAPPER_BIN_EXAMPLES_DIR ${WRAPPER_BIN_FINISHED_DIR}/examples)
set(EVERYTHING_BUILT_TARGET "EVERYTHING_BUILT_TARGET")
set(LIB_BUILT_TARGET "LIB_BUILT_TARGET")
add_custom_target(
    ${EVERYTHING_BUILT_TARGET} 
    ALL
)
add_custom_target(
    ${LIB_BUILT_TARGET}
    ALL
)
add_dependencies(${EVERYTHING_BUILT_TARGET} ${LIBNAME})
add_dependencies(${LIB_BUILT_TARGET} ${EVERYTHING_BUILT_TARGET})

add_custom_command(
    TARGET ${EVERYTHING_BUILT_TARGET} POST_BUILD
    # setting up the directories
    COMMAND sudo mkdir -p ${WRAPPER_BIN_FINISHED_DIR}
    COMMAND sudo mkdir -p ${WRAPPER_BIN_EXAMPLES_DIR}
    # commands for the library itself
    COMMAND sudo cp ${WRAPPER_BIN_DIR}/libev3dev-cpp-template-wrapper.a ${WRAPPER_BIN_FINISHED_DIR}/libev3dev-cpp-template-wrapper.a
    COMMAND sudo bash ${WRAPPER_SCRIPTS_DIR}/post_build.sh "The-Ev3Wrap-library" 500 ${WRAPPER_BIN_FINISHED_DIR}/libev3dev-cpp-template-wrapper.a 50
)
#set(ALL_LIB_FINAL_TARGETS)

add_subdirectory(examples)