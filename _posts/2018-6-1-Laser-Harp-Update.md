---
layout: post
title: Laser Harp - Update
---

I have been working on a small side project. Following the purchase of my new
Arduino micro controller, I will be building a MIDI laser harp! Read my intro
[here]({{ site.baseurl }}/2018/3/7/Laser-Harp-Init.html).

### Week 9 updates

The Laser Harp has been fleshed out, designed, and is looking much more healthy.

![current]({{ site.baseurl }}/images/laserharpupdate-current.png) ![splitter]({{ site.baseurl }}/images/laserharpupdate-splitter.png)

Just as a recap, the goals of the final product harp were:

* Simple Design
* Single Laser Module
* Frameless
* Variable # of Strings
* Polyphonic music

To accomplish this, I have arrived at a strong iteration of my design. It uses
the following large components:

* A Arduino UNO Microprocessor
* A Single Green (532 nm) 200mW Laser
* A Bipolar Stepper Motor
* A Photodiode/Amplifier pair
* A MIDI Junction

I have the following schematic planned:

![Schematic]({{ site.baseurl }}/images/laserharpupdate-schematic.png)

### Beam sensing

As discussed previously, one of the most difficult parts of this project is
sensing a broken beam, as there is no frame to actually contain the beams
themselves. My solution has been surprisingly simple. Instead of sensing light
along a beam's path, I have decided to place photo sensors to sense scattered
light in the wake of a broken beam.

![Schematic]({{ site.baseurl }}/images/laserharpupdate-scatter.png)

Obviously, the harp should need to be able to differentiate between which beam
is being scattered, but a clever design trick can be exploited. Since each beam
only exists for a short period of time (as shown in the animation below) a read
from a photo sensor at that time can be a reading corresponding to only the beam
currently being shown.

![Sweeping Beam Animation]({{ site.baseurl }}/images/laserharpinit-sweepingbeam.gif)

The following algorithm can be developed:

* For each beam:
  * Rotate mirror to beam location
  * Turn on laser
  * Read the light sensor:
    * If activated, play associated note (or continue playing associated note)
  * Turn off laser

### Deliverables

That said, the harp is starting to look quite visually impressive. The following
goals remain:

* Finalizing and smoothing out the beam splitting
* Making light sensitivity less prone to latency
* Investing in better mirrors, optical filters
* Finally - connecting this bad boy to a synthesizer!

Until next time, happy lasing!

![Laser]({{ site.baseurl }}/images/laserharpupdate-laser.jpg)
