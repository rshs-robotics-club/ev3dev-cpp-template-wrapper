---
nav_order: 8
title: "Gyro"
parent: "documentation"
grand_parent: "Ev3Wrap-unstable-docs"
---

# `Ev3Wrap::Gyro`
## public methods
---

## `static Gyro bind(ev3dev::address_type addr = ev3dev::INPUT_AUTO)`
Constructor 
{: .label .label-green }

Description: static constructor to bind to an input address.
returns the binded Gyro object. Will automatically detect which port the Gyro is connected if no parameter given.

---

## `int angle()`
getter method
{: .label .label-purple}
Untested
{: .label .label-red}
Description: the number of degrees rotated since it was placed into this mode.

>   Warning - number can exceed 0-360

---

## `int rate()`
getter method
{: .label .label-purple}
Untested
{: .label .label-red}
Description: rotational speed measured in degrees per second.

---

## `getRateAndAngle()`
getter method
{: .label .label-purple}
Untested
{: .label .label-red}
>   Warning - Do not use. use `rate()` or `angle()` instead.

---

## `int getTiltAngle()`
getter method
{: .label .label-purple}
Untested
{: .label .label-red}
>   Warning - Original documentation missing. We have no idea what this does

---

## `int getTiltRate()`
getter method
{: .label .label-purple}
Untested
{: .label .label-red}
>   Warning - Original documentation missing. We have no idea what this does

---