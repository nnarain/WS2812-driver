
#include <avr/io.h>
#include <util/delay.h>

#include "config/pinmap.h"
#include "config/timer.h"

typedef Timer<TIMERB_ADDR> TimerB;
typedef TimerDispatcher<(uint16_t)&TCNT1, 5> TimerBDispathcer;

void ledOn();
void ledOff();

int main()
{
	GpioB::init();
	led::clear();

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
	led::set();
}

void ledOff()
{
	led::clear();
}
