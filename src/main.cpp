
#include <avr/io.h>
#include <util/delay.h>

#include "config/pinmap.h"
#include "config/timer.h"

typedef Timer<TIMERB_ADDR> TimerB;
typedef TimerCallback<(uint16_t)&TCNT1, 5> TimerBHandler;

typedef void(*Callback)(void);

void ledToggleCallback();


int main()
{
	GpioB::init();
	led::clear();

	TimerB::clock_select::write(TimerB::clock_mode::CLK_256);
	TimerBHandler handler;
	handler += ledToggleCallback;

	Callback ledCallback = ledToggleCallback;

	for(;;)
	{
//		if(TCNT1 >= 31249)
//		{
//			led::toggle();
//			TCNT1 = 0;//

//			ledCallback();
//		}

		handler.poll();
	}

	return 0;
}

void ledToggleCallback()
{
	led::toggle();
	TCNT1 = 0;
}