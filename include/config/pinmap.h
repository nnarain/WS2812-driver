
#ifndef PINMAP_H
#define PINMAP_H

#include "config/portmap_328p.h"
#include "periph/bitref.h"
#include "periph/gpio_port.h"

/* TODO: Move all this stuff into main */

typedef periph::GpioPort<PORTB_ADDR, DDRB_ADDR, periph::PinSet<5>> GpioB;
typedef periph::BitRef<PORTB_ADDR, 5> led;

#endif PINMAP_H