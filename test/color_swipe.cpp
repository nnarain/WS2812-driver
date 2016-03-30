
#include <avr/io.h>

#include <WS2812/Ws2812Driver.h>
#include <stdint.h>

#include "config/portmap_328p.h"

#define LED_COUNT 60

#define RED   0xFF0000
#define GREEN 0x00FF00
#define BLUE  0x0000FF

GPIO(PORTB, DDRB, GpioB);

typedef Ws2812Driver<GpioB, 5, LED_COUNT> LedStripDriver;

int main()
{
	LedStripDriver leds;
	leds.begin();

	uint32_t colors[] = {RED, RED | GREEN, GREEN, GREEN | BLUE, BLUE, BLUE | RED};
	uint32_t colors_len = 6;

	leds.clear();
	leds.show();

	for(;;)
	{
		for(int i = 0; i < colors_len; ++i)
		{
			uint32_t color = colors[i];

			for(int j = 0; j < LED_COUNT; ++j)
			{
				leds.setPixel(j, color);
				leds.show();
				_delay_ms(10);
			}
		}
	}

	return 0;
}