---
layout: post
title: Laser-Harp-Init
---

I have been working on a small side project. Following the purchase of my new
Arduino micro controller, I will be building a MIDI laser harp!

### The Design

There are many different approaches to building one of these Sci-Fi musical
instruments, so I want to set some principles as to how I plan on making design
decisions. Ultimately, my ideal harp will fulfill the following criteria:

* It will have a simple design - I am not a team of engineers after all
* It will only use single laser module - Lasers are quite expensive and
potentially dangerous.
* Unlike a traditional harp, the laser harp will not have a frame to contain
the strings. Instead the laser beams will just travel off to infinity.
* The harp will have a variable number of strings, able to be changed at runtime
* The harp should be capable of playing multiple notes at once

In order to simulate multiple beams, the single laser will have to be pulsed at
the base, and subsequently redirected towards a mirror to give the illusion of
multiple strings.

![Sweeping Beam Animation]({{ site.baseurl }}/images/laserharpinit-sweepingbeam.gif)


### Week 1 updates - Light Sensing

One of the most worrying things about creating a robust laser harp to me is how
to accurately measure when a beam is broken. A common approach seems to be
using a photoresistor to sense laser light reflected off of a hand. I implement
the following basic circuit.

![Circuit Diagram]({{ site.baseurl }}/images/PhotoResistorA0_schem.png)

And now, on my breadboard:

![Breadboard]({{ site.baseurl }}/images/breadboard 3-7.JPG)

I then implement a simple program that reads the resistance on the analog input,
calculates the mean and standard deviation of these readings during an initial
calibration phase, and subsequently sends 'high' signals to a monitor. A
resistance signal is defined as 'high' if it is 3 standard deviations above a
computed mean.

[code]({{ site.baseurl }}/files/photo_read.ino)

Unfortunately, this model often gets a relatively small calculated standard
deviation - which I anticipate leading to potential incorrect readings in the
future. To combat this, I implement an alternate detection algorithm that relies
on an initial calibration and subsequently a exponential moving average.

[code]({{ site.baseurl }}/files/photo_read_smoothing.ino)

Below is a screenshot of readings when a flashlight is introduced near the PR.

![reads]({{ site.baseurl }}/images/arduino reads.png)

This unfortunately has a potential drawback though: prolonged light exposure
drives the running average up and may eventually make light bursts hard to
detect.



Expect updates in the next few weeks!
