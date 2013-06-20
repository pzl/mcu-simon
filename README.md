Memory Game
===========

small test program to get into embedded programming on AVR microcontrollers.

This program was written for an attiny2313a (but I don't see why this wouldn't work for other chips with similar IO) on an STK500 dev board. But any buttons and LEDs set with pull-ups and active lows on ports D and B respectively should work.

The Game
--------

First a quick light show plays, with a blinkset to show the start / get person's attention.

Then, the light sequence plays, and the user must replay the lights with the buttons. Each round one more light is added. A blinking sequence indicates success / next round.

There are no penalties for wrong guesses at the moment. But pressing an incorrect button will not light up the associated LED. The LED only lights up with a press when it is correct.

There is no pre-programmed level limit at this point, though I imagine there are physical memory limits to prevent this from going on for too long.


Issues
------

* PRNG: there is a static seed fed to the RNG at the moment, meaning the first few rounds will be strikingly similar if not identical every single play. Should use some random input for the seed. Possibly to do with user input and timing.

* Memory limit: I don't know much about memory management in MCUs yet. Don't know when this would run out of SRAM.