---
layout: default
title: "Examples folder (CMake)"
tag: "CMakeExamples"
---

## If you have not read the [first part](CMakeSpecifics.md), go read that first.
This page continues exploring the library's CMake structure, in particular everything in the `examples` folder(s)

---

### The `CMakeLists.txt` file in the `examples` folder:

```cmake
include_directories(
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
```
This tells the examples where to find the library source files, more importantly, where to find the headers.

---

```cmake
add_subdirectory(spin_a_motor)
add_subdirectory(move_until_distance)
add_subdirectory(compass_calibration)
add_subdirectory(ir_source_facer)
add_subdirectory(press_n_spin)
```
Add each of the example folders. Each example folder contains 1 example (1 executable), and 1 `CMakeLists.txt` file for managing its build process.

> Every `CMakeLists.txt` file in the individual example folders all follow the same template, with only a different project name.


---

### The template for each `CMakeLists.txt` file in the example subfolders

```cmake
project(PROJECT_NAME_HERE VERSION 1.0)
```
declares the project. Note that every example has a different `PROJECT_NAME_HERE`

---

```cmake
add_executable(
    ${PROJECT_NAME}
    ${PROJECT_NAME}.cpp
)
```
Add the example `.cpp` file to the project. (build an executable)

---

```cmake
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    ${LIBNAME}
)
```
Link the library to the example executable. Here, `${LIBNAME}` is the name of the library. (refer to [the previous page](CMakeSpecifics.md)) for more details

---

```cmake
set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}.elf
)
```
Set the executable's output file name

---

```cmake
add_dependencies(${EVERYTHING_BUILT_TARGET} ${PROJECT_NAME})
add_custom_target(
    ${PROJECT_NAME}_TARGET ALL
)
add_dependencies(${PROJECT_NAME}_TARGET ${EVERYTHING_BUILT_TARGET})
````
Make the `EVERYTHING_BUILT_TARGET` target depend on this project (be built after this project).
Make a new target named `${PROJECT_NAME}_TARGET`, then make it so that the `${PROJECT_NAME}_TARGET` target depend on the `EVERYTHING_BUILT_TARGET` target.

This means the `${PROJECT_NAME}_TARGET` will be finished once everything else is finished

---

```cmake
add_custom_command(
    TARGET ${PROJECT_NAME}_TARGET POST_BUILD
    COMMAND sudo mkdir -p ${WRAPPER_BIN_EXAMPLES_DIR}/${PROJECT_NAME}/
    COMMAND sudo cp ${WRAPPER_BIN_DIR}/examples/${PROJECT_NAME}/${PROJECT_NAME}.elf ${WRAPPER_BIN_EXAMPLES_DIR}/${PROJECT_NAME}/${PROJECT_NAME}.elf
    COMMAND sudo bash ${WRAPPER_SCRIPTS_DIR}/post_build.sh ${PROJECT_NAME} 500 ${WRAPPER_BIN_EXAMPLES_DIR}/${PROJECT_NAME}/${PROJECT_NAME}.elf 50
    USES_TERMINAL
)
```
Copy the built binary to the correct folder, then run `post_build.sh` to check its size once `${PROJECT_NAME}_TARGET` is finished.

>   variables used here such as `${WRAPPER_BIN_EXAMPLES_DIR}` are defined in higher up CMakeLists.txt files.

---

```cmake
add_dependencies(${LIB_BUILT_TARGET} ${PROJECT_NAME}_TARGET)
```
Ensure that `LIB_BUILT_TARGET` finishes after this example has been built.

---
