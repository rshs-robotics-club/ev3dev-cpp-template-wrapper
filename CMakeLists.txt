cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER "arm-linux-gnueabi-gcc")
set(CMAKE_CC_COMPILER "arm-linux-gnueabi-gcc")
set(CMAKE_CXX_COMPILER "arm-linux-gnueabi-g++")
#set(ev3dev_DIR ${PROJECT_SOURCE_DIR})

set(CUSTOM_PROJECT_NAME "ev3MotorTest")

project(${CUSTOM_PROJECT_NAME} VERSION 1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/sentFiles)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

#find_package(ev3dev)

add_executable(${CUSTOM_PROJECT_NAME} 
src/main.cpp
lib/blockable/ev3wrapblockable.hpp
lib/blockable/ev3wrapblockable.cpp
lib/motor/ev3wrapmotor.hpp
lib/motor/ev3wrapmotor.cpp
lib/motorpair/ev3wrapmotorpair.hpp
lib/motorpair/ev3wrapmotorpair.cpp
lib/touch/ev3wraptouch.hpp
lib/touch/ev3wraptouch.cpp
lib/ultrasonic/ev3wrapultrasonic.hpp
lib/ultrasonic/ev3wrapultrasonic.cpp
lib/irseeker/ev3wrapirseeker.hpp
lib/irseeker/ev3wrapirseeker.cpp
lib/compass/ev3wrapcompass.hpp
lib/compass/ev3wrapcompass.cpp
lib/color/ev3wrapcolor.hpp
lib/color/ev3wrapcolor.cpp
lib/ev3wrap.hpp
lib/ev3dev.cpp
lib/ev3dev.h

#lib/manager/commands.h
#lib/manager/commands.cpp
#lib/manager/manager.h
#lib/manager/manager.cpp
#ev3dev::ev3dev
)
#configure_file(src/main.h src/main.h)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/lib/blockable
    ${PROJECT_SOURCE_DIR}/lib/motor
    ${PROJECT_SOURCE_DIR}/lib/motorpair
    ${PROJECT_SOURCE_DIR}/lib/touch
    ${PROJECT_SOURCE_DIR}/lib/ultrasonic
    ${PROJECT_SOURCE_DIR}/lib/irseeker
    ${PROJECT_SOURCE_DIR}/lib/compass
    ${PROJECT_SOURCE_DIR}/lib/color
    #${PROJECT_SOURCE_DIR}/lib/manager

) # we know project source dir is this directory bc project was just called
#target_link_libraries(${CUSTOM_PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/libev3dev.a)
#target_include_directories(${CUSTOM_PROJECT_NAME} PUBLIC
#                           "${PROJECT_BINARY_DIR}/src"
#                           )

set_target_properties(${CUSTOM_PROJECT_NAME} PROPERTIES OUTPUT_NAME "ev3MotorTest.elf")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)