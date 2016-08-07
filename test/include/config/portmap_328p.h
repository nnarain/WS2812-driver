
#ifndef PORTMAP_328P_H
#define PORTMAP_328P_H

#include <avr/io.h>
#include <stdint.h>

#include <stdperiph/gpio_port.h>

/* GPIO */

#define REG_BASE 0x20
#define PORTB_ADDR (REG_BASE + 0x05)
#define DDRB_ADDR  (REG_BASE + 0x04)

GPIO(PORTB_ADDR, DDRB_ADDR, GpioB);

#endif // PORTMAP_328P_H
