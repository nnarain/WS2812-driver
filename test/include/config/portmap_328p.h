
#ifndef PORTMAP_328P_H
#define PORTMAP_328P_H

#include <avr/io.h>
#include <stdint.h>

/* GPIO */

#define PORTB_ADDR ((uint32_t)&PORTB)//(REG_BASE + 0x05)
#define DDRB_ADDR  ((uint32_t)&DDRB)//(REG_BASE + 0x04)

#endif // PORTMAP_328P_H
