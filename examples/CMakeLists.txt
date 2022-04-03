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