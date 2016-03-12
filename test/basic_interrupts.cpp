
#include <avr/io.h>
#include <util/delay.h>

#include <stdperiph/stdperiph.h>

#include "config/portmap_328p.h"
#include "timer.h"

using namespace stdperiph;
using namespace stdperiph::timer;

typedef Gpio<PORTB_ADDR, DDRB_ADDR> GpioB;
typedef GpioPinRef<GpioB, 5> led;

typedef Timer<TIMERB_ADDR> TimerB;
typedef TimerDispatcher<(uint16_t)&TCNT1, 5> TimerBDispathcer;

void ledOn();
void ledOff();
void ledToggle();

int main()
{
	led::mode(BitMode::OUTPUT);
	led::low();

	return 0;
}

void ledOn()
{
	led::high();
}

void ledOff()
{
	led::low();
}

void ledToggle()
{
	led::toggle();
}
