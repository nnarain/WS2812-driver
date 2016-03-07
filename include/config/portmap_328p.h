
#ifndef PORTMAP_328P_H
#define PORTMAP_328P_H

#define REG_BASE 0x20

/* GPIO */

#define PORTB_ADDR (REG_BASE + 0x05)
#define DDRB_ADDR  (REG_BASE + 0x04)

/* Timers */

#define TIMERB_ADDR (REG_BASE + 0x81)

#endif // PORTMAP_328P_H
