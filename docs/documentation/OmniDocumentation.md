---
nav_order: 11
title: "Omni"
parent: "documentation"
grand_parent: "Ev3Wrap"
---

# `Ev3Wrap::Omni`
## public methods

---

## `static Omni CreateOmni(MotorPair& leftRightPair, MotorPair& frontBackPair, CompassSensor& compass, Angle motorToCompassOffset)`
Constructor
{: .label}
Description: constructor for the omni class. MotorPairs need their motors in sequence with how their names are placed, (left then right) (front then back). A compass is required. A X motor configuration and a compass facing "fowards" will result in a 0 for motorToCompassOffset. In that case, the frontBackPair will refer to the top left and the front, and the bottom right as the back. Please measure an approximate value for motorToCompassOffset

---

## `Omni& runRelativeToMotors(float x, float y, float rpm = DEFAULT_MOTOR_RPM)`
Output method
{: .label}
Description: runs the 4 motors forever, at a speed that causes the entire robot to go in a specified vector (relative to the motors) at a specific speed.
>   Warning - We do not ensure the rpm is accurate.

---

## `Omni& runRelativeToCompass(float x, float y, float rpm = DEFAULT_MOTOR_RPM)`
Output method
{: .label}
Description: runs the 4 motors forever, at a speed that causes the entire robot to go in a specified vector (relative to where the compass faces) at a specific speed.
>   Warning - We do not ensure the rpm is accurate.

---

## `Omni& runRelativeToForwards(float x, float y, float rpm = DEFAULT_MOTOR_RPM)`
Output method
{: .label}
Description: runs the 4 motors forever, at a speed that causes the entire robot to go in a specified vector (relative to where the compass says is forwards) at a specific speed.
>   Warning - We do not ensure the rpm is accurate.

>   Tip - We're referring to the compass's `key=0` direction as forward. Refer to [the compass documentation](CompassSensorDocumentation.md) for more details.

---

## `Omni& runRelativeToMotorsTimed(float x, float y, float milliseconds, float rpm = DEFAULT_MOTOR_RPM)`
Output method
{: .label}
Affected by Blockable
{: .label .label-yellow}
Description: the timed counterpart to `runRelativeToMotors`. Will attempt to re-adjust itself to face the correct direction if it is in the "blocking" state.

---

## `Omni& runRelativeToCompassTimed(float x, float y, float milliseconds, float rpm = DEFAULT_MOTOR_RPM)`
Output method
{: .label}
Affected by Blockable
{: .label .label-yellow}
Description: the timed counterpart to `runRelativeToCompass`. Will attempt to re-adjust itself to face the correct direction if it is in the "blocking" state.

---

## `Omni& runRelativeToForwardsTimed(float x, float y, float milliseconds, float rpm = DEFAULT_MOTOR_RPM)`
Output method
{: .label}
Affected by Blockable
{: .label .label-yellow}
Description: the timed counterpart to `runRelativeToForwards`. Will attempt to re-adjust itself to face the correct direction if it is in the "blocking" state.

---