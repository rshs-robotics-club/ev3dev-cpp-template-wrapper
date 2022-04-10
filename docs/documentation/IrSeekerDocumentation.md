---
nav_order: 7
title: IrSeeker
---

# `Ev3Wrap::IrSeeker`
## public methods

---

## `static IrSeeker bind(ev3dev::address_type addr = ev3dev::INPUT_AUTO)`
Constructor 
{: .label .label-green }

Description: static constructor to bind to an input address.
returns the binded IrSeeker object. Will automatically detect which port the IrSeeker is connected if no parameter given.
>   Warning - This sensor's bind method is potentially unstable. We recommend allowing it to auto-detect instead of specifying an address.

---

## `int getDirectionAC()`
getter method
{: .label .label-purple}
Description: gets the direction of the ball from 0-9, 0 representing undetected, 5 in the middle, 1 on the left and 9 on the right side. Runs the Sensor in modulated mode (less interference from sunlight)
>   Tip - use `int getBallDirection()` instead.

---

## `int getDirectionDC()`
getter method
{: .label .label-purple}
Description: gets the direction of the ball from 0-9, 0 representing undetected, 5 in the middle, 1 on the left and 9 on the right side. Runs the Sensor in unmodulated mode (more interference from sunlight)
>   Tip - use `int getBallDirection()` instead.

---

## `std::vector<int> getAllAC()`
getter method
{: .label .label-purple}
Description: gets all 7 AC signal strength values in the IrSensor put in a `std::vector`. Each of them are measured from 0-9.

---

## `std::vector<int> getAllDC()`
getter method
{: .label .label-purple}
Description: gets all 6 DC signal strength values in the IrSensor put in a `std::vector`. Each of them are measured from 0-9.

---

## `int getACStrength()`
getter method
{: .label .label-purple}
Description: gets the signal strength from the ball (measured from 0-255) in AC (modulated mode)

---

## `int getDCStrength()`
getter method
{: .label .label-purple}
deprecated
{: .label .label-red}
Description: gets the signal strength from the ball (measured from 0-255) in DC (unmodulated mode)

---

## `int getBallDirection()`
getter method
{: .label .label-purple}
Description: returns 1 if the ball is on the right of the sensor, returns 0 if the ball is exactly in front of the sensor, returns -1 if ball is on the left of the sensor, returns -2 if ball is undetected.
>   Tip - this method relies on the AC (modulated) mode, meaning it should be more accurate and clear.

---

## `int getDirectionACDegrees()`
getter method
{: .label .label-purple}
Description: returns the direction of the ball in degrees -180 to 180. (the same range as the `CompassSensor`'s `int getRelativeDirection(int key)`)

---