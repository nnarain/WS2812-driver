
# WS2812 Led strip Driver

Generic C++ WS2812 LED strip driver

This project aims to be as generic as possible by using C++ templates and abstracting GPIO ports using its own implementation of std_periph.

Numbers used in this library can be found [here](https://www.adafruit.com/datasheets/WS2812B.pdf).

Usage
-----

As this library is header only, just add 'include' folder to your include path.

Building Tests
--------------

I'm testing the code on a Atmega328p (Arduino Pro Mini) so you will need to install avr-gcc and related libraries.


std_periph
----------

This is meant to abstract hardware ports and make is a cross platform library. When this section of the code base matures I will move it to its own repo.
