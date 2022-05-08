---
nav_order: 5
title: "Color Sensor"
parent: "Documentation-Unstable"
tag: "ColorSensor"
---

# `Ev3Wrap::ColorSensor`

## public methods
---

## `static ColorSensor bind(ev3dev::address_type addr = ev3dev::INPUT_AUTO)`
Constructor 
{: .label .label-green }

Description: static constructor to bind to an input address.
returns the binded ColorSensor object. Will automatically detect which port the ColorSensor is connected if no parameter given.

---

## `int getReflectedLightIntensity()`
getter method
{: .label .label-purple}
Description: reflected light intensity as a percentage. Note: Light on sensor is Red

---

## `int getAmbientLightIntensity()`
getter method
{: .label .label-purple}
Description: reflected ambient light intensity as a percentage. Note: Light on sensor is dimly lit blue.

---

## `Color getColor()`
getter method
{: .label .label-purple}
Description: gets the current Colour, such as `Ev3Wrap::Color::BLACK`
>   Warning: may return `Ev3Wrap::Color::NONE`

---

## `std::vector<int> getRgbColor()`
getter method
{: .label .label-purple}
Description: returns an `std::vector<int>` containing 3 integers, red, green and blue. Numbers range from 0-1020

---