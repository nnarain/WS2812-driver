
#ifndef PINREF_H
#define PINREF_H

#include <stdint.h>

#include "perph/io_port.h"

namespace perph
{

template<int PERPH_ADDR, int PIN>
class PinRef
{
public:
	static void set()
	{
		IO_PORT8(PERPH_ADDR) |= (BV(PIN));
	}

	static void clear()
	{
		IO_PORT8(PERPH_ADDR) &= ~(BV(PIN));
	}

	static void toggle()
	{
		IO_PORT8(PERPH_ADDR) ^= (BV(PIN));
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
		return IS_BIT_SET(IO_PORT8(PERPH_ADDR), PIN) != 0;
	}
};

} // namespace perph

#endif // PINREF_H
