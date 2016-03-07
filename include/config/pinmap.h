
#ifndef PINMAP_H
#define PINMAP_H

#include "config/portmap_328p.h"
#include "perph/bitref.h"
#include "perph/gpio_port.h"

typedef perph::GpioPort<PORTB_ADDR, DDRB_ADDR, perph::PinSet<5>> GpioB;
typedef perph::BitRef<PORTB_ADDR, 5> led;

#endif PINMAP_H