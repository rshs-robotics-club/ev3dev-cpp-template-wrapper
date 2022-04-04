# 
#    A CMake file used with Docker for compiling The Ev3dev C++ Wrapper Library examples
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

project(move_until_distance VERSION 1.0)

add_executable(
    ${PROJECT_NAME}
    ${PROJECT_NAME}.cpp
)
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    ${LIBNAME}
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}.elf
)
set(FINAL_EXECUTION ${FINAL_EXECUTION} "sizeBar \"spin_a_motor.elf\" \"500\" \"./bin/examples/spin_a_motor/spin_a_motor.elf\" \"50\"" PARENT_SCOPE)
list(APPEND ${FINAL_EXECUTION} "sizeBar \"spin_a_motor.elf\" \"500\" \"./bin/examples/spin_a_motor/spin_a_motor.elf\" \"50\"")
message(STATUS ${FINAL_EXECUTION})