---
title: "Utilities"
parent: "documentation"
grand_parent: "Ev3Wrap-unstable-docs"
---

# The Utilities Namespace contains many functions, most of which are contained within namespaces, not classes.
### be aware of this when using the Utilities namespace

---

## The `Beeper` namespace
used for beeping
example:
```cpp
// set future beeps to beep at 750 hertz
Ev3Wrap::Utilities::Beeper::setBeepHertz(750);
// beep for 2000 milliseconds (or 2 seconds)
// on beep
Ev3Wrap::Utilities::Beeper::setBeepDuration(2000);
// beep
Ev3Wrap::Utilities::Beeper::beep();
```

### functions:
## `static int setBeepHertz(int hertz)`
setter
{: .label .label-purple}
sets the frequency for the robot to beep at and returns the frequency given.

---

## `static int setBeepDuration(int milliseconds)`
setter
{: .label .label-purple}
sets the duration of the beep in milliseconds.
>   Tip: 1 second = 1000 milliseconds

---

## `static int setBeepRepetitions(int repeats)`
setter
{: .label .label-purple}
sets the number of times the beep will be repeated. Defaults to 1

---

## `static int setBeepRepeatDelay(int milliseconds)`
setter
{:.label .label-purple}
sets the delay between beeps in milliseconds.

---

## `static void beep(bool block)`
beeps, using config functions shown on top