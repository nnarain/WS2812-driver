
#ifndef GPIO_PORT_H
#define GPIO_PORT_H

#include "periph/io_port.h"
#include "periph/bitref.h"

namespace periph
{

template<uint8_t... PINS>
class PinSet
{
public:

	static inline uint8_t mask()
	{
		return pinMerge(PINS...);
	}

private:

	static inline uint8_t merge(uint8_t pin)
	{
		return BV(pin);
	}

	template<typename... Ints>
	static inline uint8_t merge(uint8_t pin, Ints... pins)
	{
		return BV(pin) | merge(pins...);
	}

	template<typename... Ints>
	static inline uint8_t pinMerge(Ints... pins)
	{
		return merge(pins...);
	}
};

template<
	int PERIPH_ADDR,
	int DDR_ADDR,
	class SetBits
>
class GpioPort
{
public:
	static void init()
	{
		IO_PORT8(DDR_ADDR) = SetBits::mask();
	}

private:
};

} // namespace perph

#endif // GPIO_PORT_H
