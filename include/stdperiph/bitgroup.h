
#ifndef BITGROUP_H
#define BITGROUP_H

#include "stdperiph/io_port.h"
#include "utils/bitutils.h"

#include <stdint.h>

namespace stdperiph
{

template<int N>
struct Mask
{
	enum{ value = (1 << (N-1)) | Mask<N - 1>::value };
};

template<>
struct Mask<0>
{
	enum { value = (1 << 0) };
};

template<int PERIPH_ADDR, int START_BIT, int NUM_BITS>
class BitGroup
{
public:
	static inline void write(uint8_t value)
	{
		FORCE(IO_PORT8(PERIPH_ADDR), (Mask<NUM_BITS>::value << START_BIT), value);
	}

	static inline uint8_t read()
	{
		return IO_PORT8(PERIPH_ADDR) >> START_BIT;
	}
};

} // namespace stdperiph

#endif // BITGROUP_H
