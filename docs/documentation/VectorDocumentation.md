---
title: "Vector"
nav_order: 1
tag: "Vector"
---

# `Ev3Wrap::Vector`

## Constructors
-   `Vector(float, float)`. Construct a `Vector` via its X and Y values
-   `static createVectorFromPolar(float bearing, float distance)`. Construct vector from polar coordinates

>   The `bearing` refered to in the `Vector` class starts from top (north), and continues clockwise. It is measured in degrees.

---
## public methods

---
## `float dist(Vector& otherVect = Vector::zero)`
getter
{: .label .label-purple}
Description: gets the length of the vector. If another vector is specified, they are treated as position vectors and it gets the distance between the 2.

---
## `float getBearing(Vector& otherVect = Vector::zero)`
getter
{: .label .label-purple}
Description: gets the bearing of the vector. If another vector is specified, it gets the clockwise angle from this vector to the other vector (may be negative)

---