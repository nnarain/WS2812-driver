
#ifndef BITREF_H
#define BITREF_H

#include <stdint.h>

#include "periph/io_port.h"

namespace periph
{

template<int PERIPH, int PIN>
class BitRef
{
public:
	static void high()
	{
		IO_PORT8(PERIPH) |= (BV(PIN));
	}

	static void low()
	{
		IO_PORT8(PERIPH) &= ~(BV(PIN));
	}

	static void toggle()
	{
		IO_PORT8(PERIPH) ^= (BV(PIN));
	}

	static void set(bool val)
	{
		if(val)
			high();
		else
			low();
	}

	static bool value()
	{
		return IS_BIT_SET(IO_PORT8(PERIPH), PIN) != 0;
	}
};

} // namespace perph

#endif // BITREF_H
