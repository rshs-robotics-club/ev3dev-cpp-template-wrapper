---
layout: default
title: Motor documentation
nav_order: 1
parent: documentation
---
# `Ev3Wrap::Motor`
## public methods
---
### `Motor bind(ev3dev::address_type)`

Constructor 
{: .label .label-green }

Description: static constructor to bind to an output address.
returns the binded motor object.

---
### `Motor& runTimed(float milliseconds, float rpm = DEFAULT_MOTOR_RPM)`
Affected by blockable  {: .label .label-yellow }
Output method {: .label }

Description: tells the motor to run for a specific number of milliseconds at a specific rpm.
Returns a reference of the Motor itself so that method chaining can be done.

---

### `Motor& runForever(float rpm = DEFAULT_MOTOR_RPM)`
Output method {: .label}

Description: tells the motor to run at a specific rpm

---

### `Motor& runToAbsPos(float pos, float rpm = DEFAULT_MOTOR_RPM)`
Output method {: .label }
Unstable/Untested {: .label .label-red }
Affected by Blockable {: .label .label-yellow }
Description: tells the motor to run to a specific position.

---

### `Motor::runToRelPos(float relPos, float rpm = DEFAULT_MOTOR_RPM)`
Output method {: .label }
Unstable/Untested {: .label .label-red }
Affected by Blockable {: .label .label-yellow }
Description: tells the motor to run to a position relative to the motor's current position

---

### `Motor::holdPosition()`
Output method {: .label }
Description: tells the motor to stop whilst resisting any force trying to budge / move the motor.

---

### `Motor::releaseMotor()`
Output method {: .label }
Description: tells the motor to cut it's electricity and freely come to a stop.

---
# End