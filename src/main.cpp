
#include <avr/io.h>
#include <util/delay.h>

#include "config/pinmap.h"
#include "config/timer.h"

typedef Timer<TIMERB_ADDR> TimerB;
typedef TimerDispatcher<(uint16_t)&TCNT1, 5> TimerBDispathcer;

void ledToggleCallback();

int main()
{
	GpioB::init();
	led::clear();

	TimerB::clock_select::write(TimerB::clock_mode::CLK_256);
	
	TimerBDispathcer dispatcher;
	
	dispatcher.setMaxTimerCount(32429);

	TimerHandler handler;
	handler.timeout = 32429;
	handler.callback = ledToggleCallback;

	dispatcher += &handler;

	for(;;)
	{
		dispatcher.poll();
	}

	return 0;
}

void ledToggleCallback()
{
	led::toggle();
}