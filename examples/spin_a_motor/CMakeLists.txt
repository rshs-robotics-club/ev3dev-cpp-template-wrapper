project(spin_a_motor VERSION 1.0)

add_executable(
    ${PROJECT_NAME}
    spin_a_motor.cpp
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