
#ifndef GPIO_PIN_REF_H
#define GPIO_PIN_REF_H

namespace stdperiph
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
	static inline void mode(BitMode::e mode)
	{
		if(mode == BitMode::OUTPUT)
			IO_PORT8(Gpio::DDR) |= (1 << PIN);
		else
			IO_PORT8(Gpio::DDR) &= ~(1 << PIN);
	}

	static inline void high()
	{
		IO_PORT8(Gpio::PERIPH) |= (BV(PIN));
	}

	static inline void low()
	{
		IO_PORT8(Gpio::PERIPH) &= ~(BV(PIN));
	}

	static inline void toggle()
	{
		IO_PORT8(Gpio::PERIPH) ^= (BV(PIN));
	}

	static inline void set(uint8_t val)
	{
		FORCE(IO_PORT8(Gpio::PERIPH), BV(PIN), (val << PIN));
	}

	static inline bool value()
	{
		return IS_BIT_SET(IO_PORT8(Gpio::PERIPH), PIN) != 0;
	}
};

} // namespace stdperiph

#endif
