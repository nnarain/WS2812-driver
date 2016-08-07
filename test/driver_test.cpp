
#include <avr/io.h>

#include <WS2812/Ws2812Driver.h>
#include <stdint.h>

#include "config/portmap_328p.h"

#define LED_COUNT 60

#define RED   0xFF0000
#define GREEN 0x00FF00
#define BLUE  0x0000FF

typedef Ws2812Driver<GpioB, 5, LED_COUNT> LedStripDriver;

int main()
{
	LedStripDriver leds;

	leds.begin();

	leds.setPixels(0, LED_COUNT / 2, GREEN);
	leds.setPixels((LED_COUNT / 2) + 1, LED_COUNT, GREEN);

	leds.show();

	for(;;)
	{
		leds.adjustBrightness(0, LED_COUNT / 2, 0.1f);
		leds.show();
		_delay_ms(1000);

		leds.setPixels(0, LED_COUNT / 2, GREEN);
		leds.show();
		_delay_ms(1000);
	}

	return 0;
}