---
title: "MotorPair"
nav_order: 3
parent: "Documentation-Unstable"
grand_parent: "Ev3Wrap-unstable-docs"
---

# `Ev3Wrap::MotorPair`
## public methods
---
## `static MotorPair CreateMotorPair(Ev3Wrap::Motor& m1, Ev3Wrap::Motor& m2)`
Constructor 
{: .label .label-green }
Description: static constructor for creating a "manager" class. Parameters must be placed in order, from left to right.

---

## `MotorPair& runMotorsForever(float rpm1 = 50, float rpm2 = 50)`
Output method
{: .label}
Description: runs the 2 motors forever at certain speeds. Calls the motor's `runForever` internally.

---

## `MotorPair& runMotorsTimed(float milliseconds, float rpm1 = 50, float rpm2 = 50)`
Output method
{: .label}
Affected by Blockable
{: .label .label-yellow}
Description: runs the motors for a set number of seconds, then stops the motors.
>   Warning - This relies on the motors not `isBlocking`

---

## `MotorPair& stopMotors()`
Output method
{: .label}
Description: tells the motors to stop whilst resisting any force trying to budge / move the motor.

---

## `MotorPair& releaseMotors()`
Output method
{: .label}
Description: tells the motors to cut its electricity and freely come to a stop.

---