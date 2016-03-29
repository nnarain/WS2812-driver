
# WS2812 Led strip Driver

AVR WS2812 C++ LED strip driver

This project is a C++ driver for WS2812 LED strips.

Numbers used in this library can be found [here](https://www.adafruit.com/datasheets/WS2812B.pdf).

Usage
-----

As this library is header only, just add 'include' folder to your include path.

Building Tests
--------------

I'm testing the code on a Atmega328P so you will need to install avr-gcc and related libraries.


stdperiph
----------

This is meant to abstract hardware ports and make is a cross platform library. When this section of the code base matures I will move it to its own repo.
