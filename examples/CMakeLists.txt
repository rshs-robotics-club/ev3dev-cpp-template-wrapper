# 
#    A CMake file used with Docker for compiling The Ev3dev C++ Wrapper Library
#
#    Copyright (c) 2021, 2022 - Eisverygoodletter
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

# this file is mainly for including sub-folders which contains examples of how to use the library
# it is not meant to be a full test suite (difficult due to the nature of this library)
include_directories(
    ${CMAKE_SOURCE_DIR}/lib/
    ${CMAKE_SOURCE_DIR}/lib/blockable/
    ${CMAKE_SOURCE_DIR}/lib/button/
    ${CMAKE_SOURCE_DIR}/lib/color/
    ${CMAKE_SOURCE_DIR}/lib/compass/
    ${CMAKE_SOURCE_DIR}/lib/gyro/
    ${CMAKE_SOURCE_DIR}/lib/irseeker/
    ${CMAKE_SOURCE_DIR}/lib/motor/
    ${CMAKE_SOURCE_DIR}/lib/motorpair/
    ${CMAKE_SOURCE_DIR}/lib/omnirobot/
    ${CMAKE_SOURCE_DIR}/lib/touch/
    ${CMAKE_SOURCE_DIR}/lib/ultrasonic/
)



add_subdirectory(spin_a_motor)
add_subdirectory(move_until_distance)