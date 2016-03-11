
#ifndef GPIO_PIN_REF_H
#define GPIO_PIN_REF_H

namespace periph
{
namespace BitMode
{
	enum e
	{
		OUTPUT = 1,
		INPUT  = 0
	};
}

template<typename Gpio, int PIN>
class GpioPinRef
{
public:
	static void mode(BitMode::e mode)
	{
		if(mode == BitMode::OUTPUT)
			IO_PORT8(Gpio::DDR) |= (1 << PIN);
		else
			IO_PORT8(Gpio::DDR) &= ~(1 << PIN);
	}

	static void high()
	{
		IO_PORT8(Gpio::PERIPH) |= (BV(PIN));
	}

	static void low()
	{
		IO_PORT8(Gpio::PERIPH) &= ~(BV(PIN));
	}

	static void toggle()
	{
		IO_PORT8(Gpio::PERIPH) ^= (BV(PIN));
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
		return IS_BIT_SET(IO_PORT8(Gpio::PERIPH), PIN) != 0;
	}
};

}

#endif
