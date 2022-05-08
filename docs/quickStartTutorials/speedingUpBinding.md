---
layout: default
title: "The `bind` method"
parent: "Quick Start"
nav_order: 2
tag: "SpeedingUpBindingTutorial"
---

## This tutorial includes: 

## What is the bind method?
In order for your code to be able to use any motor or sensor, you must specify what port that motor / sensor is currently at.
The purpose of the bind method is to make this process easier.

## What the bind method does:
The bind method takes in a string that represents the name of the motor / sensor you want to bind. To be specific, a `constexpr char` array that represents the port name.
##### Why does the documentation say that the bind method takes in an `ev3dev::address_type` ?
The reason for this, is that the `ev3dev::address_type` is a `typedef`, in other words, an alternative name for `constexpr char`. The other tutorials will tell you that you can use `Ev3Wrap::&lt;type&gt;::OUTPUT_A` instead of a `constexpr char` array. These are in fact static variables that contain the port names.

## How to speed it up
When in a competition, it is often the case that you want your code to start as fast as possible, and the `bind` method is usually the bottleneck in most cases.
##### Dissecting the inner workings of the bind method
The bind method defaults its port to `INPUT_AUTO` if no port is specified. While this is good for debugging purposes, it is very slow as it has to search through all the ports to find the one that is not in use.
The sensors can also have different communication standards, for example although both the `IrSeeker` and the `CompassSensor` uses the same `i2c` standard, the `IrSeeker`'s address defaults to the 8th byte and the `CompassSensor`'s address defaults to the 1st byte.
##### TL:DR How do you speed it up?
Manually specify the port instead of making it detect the port automatically