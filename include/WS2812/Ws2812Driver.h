
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
	static const unsigned int NUM_LEDS = LED_COUNT;
	static const unsigned int PIXEL_BUFFER_SIZE = LED_COUNT * 3;
	static const unsigned int MASK = (1 << PIN);

private:
	uint8_t pixels_[PIXEL_BUFFER_SIZE]; // 24 bit color GRB order

public:
	Ws2812Driver()
	{
	}

	~Ws2812Driver()
	{
	}

	/**
		\brief initialize the LED strip
	*/
	void begin()
	{
		// enable output
		IO_PORT8(GPIO::DDR) |= MASK;
	}

	/**
		\brief Set pixel color

		\param r Red
		\param g Green
		\param b Blue
	*/
	void setPixel(uint16_t pixel, uint8_t r, uint8_t g, uint8_t b)
	{
		// load color components in GRB order
		uint16_t idx = pixel * 3;
		pixels_[idx + 0] = g;
		pixels_[idx + 1] = r;
		pixels_[idx + 2] = b;
	}

	/**
		\brief update the led strip
	*/
	void show()
	{
		sendBuffer(pixels_, PIXEL_BUFFER_SIZE);

		// hold signal low for minimum 50 us to load new colors into PWN registers
		_delay_us(50);
	}

	/* Convinence functions */

	/**
		\brief set pixel with a single RGB value
	*/
	void setPixel(uint16_t pixel, uint32_t color)
	{
		uint8_t r = (color & 0xFF0000) >> 16;
		uint8_t g = (color & 0x00FF00) >> 8;
		uint8_t b = (color & 0x0000FF) >> 0;

		setPixel(pixel, r, g, b);
	}

	/**
		\brief Set a range of pixels

		\param start start index
		\param end end idex
		\param color color
	*/
	void setPixels(uint16_t start, uint16_t end, uint32_t color)
	{
		if(start > end) return;

		for(uint16_t i = start; i < end; ++i)
		{
			setPixel(i, color);
		}
	}

	/**
		Get led color at index
	*/
	uint32_t getPixel(uint16_t pixel)
	{
		uint16_t idx = pixel * 3;
		uint32_t g = pixels_[idx + 0];
		uint32_t r = pixels_[idx + 1];
		uint32_t b = pixels_[idx + 2];

		return ((g << 16) | (r << 8) | (b));
	}

	/**
		Fade led color
	*/
	void adjustBrightness(uint16_t pixel, float value)
	{
		uint16_t idx = pixel * 3;
		uint8_t g = pixels_[idx + 0];
		uint8_t r = pixels_[idx + 1];
		uint8_t b = pixels_[idx + 2];

		uint8_t g2 = (uint8_t)((float)g * value);
		uint8_t r2 = (uint8_t)((float)r * value);
		uint8_t b2 = (uint8_t)((float)b * value);

		setPixel(pixel, r2, g2, b2);
	}

	/**
		\brief Adjust brightness for range
	*/
	void adjustBrightness(uint16_t start, uint16_t end, float value)
	{
		for(int i = start; i < end; ++i)
		{
			adjustBrightness(i, value);
		}
	}

	/**
		\brief Blank all the leds
	*/
	void clear()
	{
		for(int i = 0; i < LED_COUNT; ++i)
		{
			setPixel(i, 0, 0, 0);
		}
	}

private:
	void sendBuffer(uint8_t * buffer, uint16_t len)
	{
		uint8_t * pBuf = buffer;
		uint8_t count;
		uint8_t data;
		uint8_t maskhi, masklo;

		// mask off interrupts so cycles are exclusive to this sequence
		cli();

		maskhi = IO_PORT8(GPIO::PERIPH) | MASK;
		masklo = IO_PORT8(GPIO::PERIPH) | ~MASK;

		// loop for every byte in the buffer
		while(len--)
		{
			data = *pBuf++;

			// for each byte ...
			asm volatile(
				"			ldi %[count], 8" 		"\n\t" // load bit counter
				"1:"
				"			out %[port], %[maskhi]"	"\n\t" // signal high (t0)
				DELAY_04_US								   // delay to t1
				"			sbrs %[data], 7"		"\n\t" // check if the bit we're writing is high, if not, signal low (t1)
				"			out %[port], %[masklo]"	"\n\t" //
				DELAY_04_US								   // delay to t2
				"			out %[port], %[masklo]"	"\n\t" // signal low (t2)
				DELAY_04_US
				"			lsl %[data]"			"\n\t" // shift the bit we are processing
				"			dec %[count]"			"\n\t" // decrease the bit counter
				"			brne 1b"				"\n\t" // loop back to start if more bits in the byte to write

				:
				: [count] "d" (count), [port] "I" (_SFR_IO_ADDR(IO_PORT8(GPIO::PERIPH))), [data] "r" (data), [maskhi] "d" (maskhi), [masklo] "d" (masklo)
			);
		}

		// re-enable interrupts
		sei();
	}
};

#endif
