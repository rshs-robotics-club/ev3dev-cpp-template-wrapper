---
title: "Compass Sensor"
nav_order: 4
parent: "Documentation-Unstable"
grand_parent: "Ev3Wrap-unstable-docs"
---
# `Ev3Wrap::CompassSensor`

## public methods
---

## `static CompassSensor bind(ev3dev::address_type addr = ev3dev::INPUT_AUTO)`
Constructor 
{: .label .label-green }

Description: static constructor to bind to an input address.
returns the binded CompassSensor object. Will automatically detect which port the CompassSensor is connected if no parameter given.

---

## `int getAbsoluteDirection()`
getter method
{: .label .label-purple}
Description: gets the current direction from 0 - 379 degrees. Note: `int getRelativeDirection()` is recommended

---

## `CompassSensor& setZero(int key = 0)`
setter method
{: .label .label-purple}
Description: sets the `key`'s relative direction 0 to the current direction.

---

## `int getRelativeDirection(int key = 0)`
getter method
{: .label .label-purple}
Description: gets the current direction from -180 - 180 degrees, relative to the `key`'s setZero direction.

---

## `int getDegreeOffset(int key = 0)`
getter method
{: .label .label-purple}
Description: gets the degree offset (offset is measured from getAbsoluteDirection()) for the `key`.

---

## `static int compareAngles(float sourceAngle, float otherAngle, float tolerance = 10)`
math tool
{: .label}
Description: if `sourceAngle` is on the left of `otherAngle`, return 1. If `sourceAngle` and `otherAngle` are close to each other (in the range of `tolerance * 2`), return 0. If `sourceangle` is on the right of `otherAngle`, return -1

---

## `void beginCalibrate` & `void endCalibrate`

Description: refer to the tutorials linked below
(tutorials todo)

---