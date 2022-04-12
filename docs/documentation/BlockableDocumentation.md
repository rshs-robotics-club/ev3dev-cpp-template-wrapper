---
title: "Blockable"
nav_order: 1
parent: "documentation"
grand_parent: "Ev3Wrap"
---
# `Ev3Wrap::Blockable`
> Important Information: This class is meant to be inherited by other classes to allow them to have a "blocked" state. Use `setBlocking` and `getBlocking` to access the "blocked state". When child classes are not in the "blocked state", after any timed method calls, the thread will not be blocked

## public methods
---

## `blockableReturn setBlocking(bool willBlock)`
setter
{: .label .label-purple}
Description: returns the derived child class and sets the blocking state.

---

## `bool getBlocking()`
getter
{: .label .label-purple}
Description: returns the current blocking state.

---

## protected methods
---
## `void blockMilliseconds(float milliseconds, std::function<void()> cleanupFunction = []{})`
Affected by Blockable
{: .label .label-yellow}
Description: blocks the thread for an amount of seconds, then calls the cleanup function. This method will NOT do anything if the blocking state is false

---

## `void blockUntilStateReached(std::function<bool()> state, float loopSpeed = 5, std::function<void()> cleanupFunction = []{})`
Affected by Blockable
{: .label .label-yellow}
Description: blocks the thread in a while loop, and executes the `state` function every `loopSpeed` milliseconds. Once the `state` function returns true, the loop breaks and `cleanupFunction` is called.
This method will NOT do anything if the blocking state is false

---

## `void blockMillisecondsAndFire(std::function<void()> function, float milliseconds, std::function<void()> cleanupFunction = []{})`
Affected by Blockable
{: .label .label-yellow}
Description: blocks the thread in a while loop, and executes the `function` CONSTANTLY (not delays). after `milliseconds`, break out of the while loop and call `cleanupFunction`.
>   Warning - do not put hardware intensive / damaging commands into this method. It DOES NOT wait for a cooldown, and will execute `function` as fast as it can. You might fry / damage a motor (untested).
> 
This method will NOT do anything if the blocking state is false

---
