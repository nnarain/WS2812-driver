
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

int main()
{
	led::mode(BitMode::OUTPUT);
	led::low();

	TimerB::clock_select::write(TimerB::clock_mode::CLK_256);
	
	TimerBDispathcer dispatcher;
	
	dispatcher.setMaxTimerCount(51000);

	TimerHandler ledOnHandler;
	ledOnHandler.timeout = 25000;
	ledOnHandler.callback = ledOn;

	TimerHandler ledOffHandler;
	ledOffHandler.timeout = 50000;
	ledOffHandler.callback = ledOff;

	dispatcher += &ledOnHandler;
	dispatcher += &ledOffHandler;

	for(;;)
	{
		dispatcher.poll();
	}

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
