
#include <avr/io.h>
#include <util/delay.h>

#include "stdperiph/gpio_port.h"
#include "stdperiph/gpio_pin_ref.h"

using namespace stdperiph;

// setup Gpio port B
GPIO(PORTB, DDRB, GpioB);

typedef GpioPinRef<GpioB, 5> DebugLed;

int main()
{
	DebugLed::mode(BitMode::OUTPUT);
	DebugLed::low();

	for(;;);

	return 0;
}
