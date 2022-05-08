---
nav_order: 9
title: "Ultrasonic Sensor"
parent: "Documentation-Unstable"
tag: "UltrasonicSensor"
---

# `Ev3Wrap::UltrasonicSensor`
## public methods

---

## `static UltrasonicSensor bind(ev3dev::address_type addr = ev3dev::INPUT_AUTO)`
Constructor 
{: .label .label-green }

Description: static constructor to bind to an input address.
returns the binded UltrasonicSensor object. Will automatically detect which port the UltrasonicSensor is connected if no parameter given.

---

## `float getCentimetres()`
getter method
{: .label .label-purple}
Description: get distance measured in centimetres.

---

## `bool getSensorsNearby()`
getter method
{: .label .label-purple}
Untested
{: .label .label-red}
Description: check if there are other ultrasonic sensors nearby.

---