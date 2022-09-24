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

cmake_minimum_required(VERSION 3.24.0)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER "arm-linux-gnueabi-gcc")
set(CMAKE_CC_COMPILER "arm-linux-gnueabi-gcc")
set(CMAKE_CXX_COMPILER "arm-linux-gnueabi-g++")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(LIBNAME "ev3-cpp-template-wrapper-lib")
project(${LIBNAME} VERSION 3.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
message(STATUS ${OPTIMIZATION_LEVEL})
add_compile_options(${OPTIMIZATION_LEVEL})
# unfortunately there are problems in 
# libbluetooth so we must use -fpermissive
add_compile_options(-fpermissive)
add_definitions(-DDEBUG_MODE_ENABLED)
add_library(
    ${LIBNAME} 
    STATIC
    lib/bbr-irseeker/bbr-irseeker.cpp

    lib/button/button.cpp
    
    lib/hitechnic-compass/hitechnic-compass.cpp

    lib/hitechnic-irseeker/hitechnic-irseeker.cpp

    lib/motor/motor.cpp

    lib/color-sensor/color-sensor.hpp
    lib/gyro-sensor/gyro.hpp

    lib/omni/omni.cpp

    lib/vector/vector.cpp

    lib/bluetooth-socket/bluetooth-socket.cpp

    lib/ev3dev.cpp
    lib/smbus.cpp
)
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

target_include_directories(
    ${LIBNAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/lib/
)

SUBDIRLIST(SUBDIRS ${PROJECT_SOURCE_DIR}/lib/)
foreach(subdir ${SUBDIRS})
    message(STATUS ${subdir})
    target_include_directories(${LIBNAME} PUBLIC ${PROJECT_SOURCE_DIR}/lib/${subdir})
endforeach()
target_include_directories(${LIBNAME} PUBLIC /home/compiler/crossCompileLibraries/libbluetooth/include/)
target_link_libraries(${LIBNAME} PRIVATE /home/compiler/crossCompileLibraries/libbluetooth/lib/arm-linux-gnueabi/libbluetooth.a)

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
if (${VERBOSE})
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
endif()