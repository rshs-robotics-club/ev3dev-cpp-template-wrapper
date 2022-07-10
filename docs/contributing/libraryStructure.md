---
layout: default
title: "Library Structure"
nav_order: 1
tag: "libraryStructure"
---

# this page talks about how the library is structured

### Prerequisites:
- Basic CMake knowledge
- Basic C/C++ knowledge
- Basic Docker knowledge


---

### the basic library folder structure

```
- ev3dev-cpp-template-wrapper
    - .github
    - .vscode
    - docs
        - contributing
        - documentation
        - quickStartTutorials
    - examples
        - compass_calibration
        - ir_source_facer
        - move_until_distance
    - lib
        - blockable
        - button
        - color
        - compass
        - gyro
        - irseeker
        - motor
    - scripts

```
- github workflows, such as compile testing and documentation management are in the `.github` folder
- all documentation is placed within the `docs` folder. To go into this with more detail, refer to [this] (TODO, page hasn't been made)
- examples are compiled with the library in the `examples` folder. Each folder inside is 1 example. They are always kept up to date with the version of the library
- The source code of the library is stored within the `lib` folder. Each folder inside corresponds to 1 functionality of the library.
- bash scripts used for compilation is stored in the `scripts` folder.