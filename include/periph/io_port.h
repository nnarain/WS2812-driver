
#ifndef IO_PORT_H
#define IO_PORT_H

#include <stdint.h>

#include "utils/bitutils.h"

#define IO_PORT8(addr)  (*((volatile uint8_t * const) addr))
#define IO_PORT16(addr) (*((volatile uint16_t * const) addr))

#endif // IO_PORT_H
