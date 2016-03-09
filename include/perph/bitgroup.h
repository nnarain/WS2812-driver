
#ifndef BITGROUP_H
#define BITGROUP_H

#include "perph/io_port.h"
#include "utils/bitutils.h"

#include <stdint.h>

namespace perph
{

template<int N>
struct Mask
{
	enum{ value = (1 << N) | Mask<N - 1>::value };
};

template<>
struct Mask<1>
{
	enum { value = 0x01 };
};

template<int PERPH_ADDR, int START_BIT, int NUM_BITS>
class BitGroup
{
public:
	static inline void write(uint8_t value)
	{
		FORCE(IO_PORT8(PERPH_ADDR), (Mask<NUM_BITS>::value << START_BIT), value);
	}

	static inline uint8_t read()
	{
		return IO_PORT8(PERPH_ADDR) >> START_BIT;
	}
};

}

#endif // BITGROUP_H
