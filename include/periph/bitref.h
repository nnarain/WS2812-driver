
#ifndef BITREF_H
#define BITREF_H

#include <stdint.h>

#include "periph/io_port.h"

namespace periph
{

template<int PERIPH_ADDR, int PIN>
class BitRef
{
public:
	static void set()
	{
		IO_PORT8(PERIPH_ADDR) |= (BV(PIN));
	}

	static void clear()
	{
		IO_PORT8(PERIPH_ADDR) &= ~(BV(PIN));
	}

	static void toggle()
	{
		IO_PORT8(PERIPH_ADDR) ^= (BV(PIN));
	}

	static void setState(bool val)
	{
		if(val)
			set();
		else
			clear();
	}

	static bool value()
	{
		return IS_BIT_SET(IO_PORT8(PERIPH_ADDR), PIN) != 0;
	}
};

} // namespace perph

#endif // BITREF_H
