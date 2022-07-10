---
nav_order: 11
title: "Omni"
parent: "Documentation-Unstable"
tag: "Omni"
---

The base assumption of the `Omni` class is that it is created where there are 4 motors, each facing out from the center, oriented 90 degrees from each other.

The top left motor is named the E motor, the top right motor is named the F motor, the bottom right motor is named the G motor, and the bottom left motor is named the H motor.
# `Ev3Wrap::Omni`
## public methods

---

## `Omni& controlRaw(float eSpeed, float fSpeed, float gSpeed, float hSpeed);`
Output method
{: .label}

directly control the speed of the motors.