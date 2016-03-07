
#include <avr/io.h>
#include <util/delay.h>

#include "config/pinmap.h"

int main()
{
	GpioB::init();

	for(;;)
	{
		led::toggle();
		_delay_ms(1000);
	}

	return 0;
}
