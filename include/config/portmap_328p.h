
#ifndef PORTMAP_328P_H
#define PORTMAP_328P_H

#include <avr/io.h>
#include <stdint.h>

#define REG_BASE 0x20

/* GPIO */

#define PORTB_ADDR ((uint32_t)&PORTB)//(REG_BASE + 0x05)
#define DDRB_ADDR  ((uint32_t)&DDRB)//(REG_BASE + 0x04)

/* Timers */

#define TIMERB_ADDR ((uint32_t)&TCCR1B) //(REG_BASE + 0x81)

#endif // PORTMAP_328P_H
