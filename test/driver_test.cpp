
#include <avr/io.h>

#include <WS2812/Ws2812Driver.h>
#include <stdint.h>

#include "config/portmap_328p.h"

#define LED_COUNT 40

GPIO(PORTB, DDRB, GpioB);

typedef Ws2812Driver<GpioB, 5, LED_COUNT> LedStripDriver;

int main()
{
	LedStripDriver leds;

	leds.begin();

	for(int i = 0; i < LED_COUNT; ++i)
	{
		if(i < LED_COUNT / 2)
		{
			leds.setPixel(i, 0, 0, 255);
		}
		else
		{
			leds.setPixel(i, 255, 0, 0);
		}
	}

	leds.show();

	for(;;)
	{
	}

	return 0;
}