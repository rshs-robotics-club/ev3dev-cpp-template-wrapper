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

project(compass_calibration VERSION 1.0)

add_executable(
    ${PROJECT_NAME}
    ${PROJECT_NAME}.cpp
)
# link the Ev3Wrap library
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    ${LIBNAME}
)
# set its output executable name
set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}.elf
)
# make sure the EVERYTHING_BUILT_TARGET target is built AFTER this project is built.
add_dependencies(${EVERYTHING_BUILT_TARGET} ${PROJECT_NAME})
# create a custom target for this project that will be executed AFTER the EVERYTHING_BUILT_TARGET
# is executed
add_custom_target(
    ${PROJECT_NAME}_TARGET ALL
)
# make sure this custom target of ours is executed after the EVERYTHING_BUILT_TARGET is built
add_dependencies(${PROJECT_NAME}_TARGET ${EVERYTHING_BUILT_TARGET})
# add a custom command that:
# 1. creates the folder for this project in the finished examples folder
# 2. copies the finished executable from the messy bin to the bin/finished folder
# 3. executes a bash script that shows a bar checking for the executable's size
add_custom_command(
    TARGET ${PROJECT_NAME}_TARGET POST_BUILD
    COMMAND mkdir -p ${WRAPPER_BIN_EXAMPLES_DIR}/${PROJECT_NAME}/
    COMMAND cp ${WRAPPER_BIN_DIR}/examples/${PROJECT_NAME}/${PROJECT_NAME}.elf ${WRAPPER_BIN_EXAMPLES_DIR}/${PROJECT_NAME}/${PROJECT_NAME}.elf
    COMMAND ${WRAPPER_SCRIPTS_DIR}/post_build.sh ${PROJECT_NAME} 500 ${WRAPPER_BIN_EXAMPLES_DIR}/${PROJECT_NAME}/${PROJECT_NAME}.elf 50
    USES_TERMINAL
)
add_dependencies(${LIB_BUILT_TARGET} ${PROJECT_NAME}_TARGET)