
#ifndef WS2812DRIVER_H
#define WS2812DRIVER_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdint.h>

#include "stdperiph/gpio_port.h"

#define NOP   "nop\n\t"
#define NOP2  NOP NOP
#define NOP4  NOP2 NOP2
#define NOP8  NOP4 NOP4
#define NOP16 NOP8 NOP8

#define DELAY_04_US NOP4 NOP2

template <typename GPIO, uint8_t PIN, uint16_t LED_COUNT>
class Ws2812Driver
{
public:
	static const unsigned int PIXEL_BUFFER_SIZE = LED_COUNT * 3;
	static const unsigned int MASK = (1 << PIN);

private:
	uint8_t pixels_[PIXEL_BUFFER_SIZE]; // 24 bit color

public:
	Ws2812Driver()
	{
	}

	~Ws2812Driver()
	{

	}

	void begin()
	{
		// enable output
		IO_PORT8(GPIO::DDR) |= MASK;
	}

	void setPixel(uint16_t pixel, uint8_t r, uint8_t g, uint8_t b)
	{
		uint16_t idx = pixel * 3;
		pixels_[idx + 0] = g;
		pixels_[idx + 1] = r;
		pixels_[idx + 2] = b;
	}

	void show()
	{
		sendBuffer(pixels_, PIXEL_BUFFER_SIZE);
		_delay_us(50);
	}

private:
	inline void sendBuffer(uint8_t * buffer, uint16_t len)
	{
		uint8_t * pBuf = buffer;
		uint8_t count;
		uint8_t data;
		uint8_t maskhi, masklo;

		cli();

		maskhi = IO_PORT8(GPIO::PERIPH) | MASK;
		masklo = IO_PORT8(GPIO::PERIPH) | ~MASK;

		while(len--)
		{
			data = *pBuf++;

			asm volatile(
				"			ldi %[count], 8" 		"\n\t" // load bit counter
				"loop:"
				"			out %[port], %[maskhi]"	"\n\t" // signal high (t0)
				DELAY_04_US								   // delay to t1
				"			sbrs %[data], 7"		"\n\t" // check if the bit we're writing is high, if not, signal low (t1)
				"			out %[port], %[masklo]"	"\n\t" //
				DELAY_04_US								   // delay to t2
				"			out %[port], %[masklo]"	"\n\t" // signal low (t2)
				DELAY_04_US
				"			lsl %[data]"			"\n\t" // shift the bit we are processing
				"			dec %[count]"			"\n\t" // decrease the bit counter
				"			brne loop"				"\n\t" // loop back to start if more bits in the byte to write

				:
				: [count] "d" (count), [port] "I" (_SFR_IO_ADDR(IO_PORT8(GPIO::PERIPH))), [data] "r" (data), [maskhi] "d" (maskhi), [masklo] "d" (masklo)
			);
		}

		sei();
	}
};

#endif
