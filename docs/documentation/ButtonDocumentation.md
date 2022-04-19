---
nav_order: 10
title: "Button"
parent: "Documentation-Unstable"
tag: "Button"
---

# `Ev3Wrap::Button`
> Tip - Although the `Ev3Wrap::Button` class inherits from `Ev3Wrap::Blockable`, it is privately inherited unlike the other classes. It is always in the "blocking" state, since there is no need for a non "blocking" state in this class.

## public methods

---

## `static Button CreateButton(ButtonCode btnCode)`
Constructor
{: .label .label-green}
Description: creates a button.
>   Warning - We do not guarantee that `ButtonCode::BACK` would work

---

## `bool isPressed()`
getter method
{: .label .label-purple}
Description: checks if the button is currently pressed / held down

---

## `Button& blockUntilPressed()`
getter method
{: .label .label-purple}
Affected by Blockable
{: .label .label-yellow}
Description: blocks the current thread until the button is pressed.

---

## `blockUntilReleased()`
getter method
{: .label .label-purple}
Affected by Blockable
{: .label .label-yellow}
Description: blocks the current thread until the button is pressed. Then, measure how long the user holds down the button for, then returns the amount of time in milliseconds.

---