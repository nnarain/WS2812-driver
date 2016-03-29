
#include <avr/io.h>
#include <util/delay.h>

#include <stdperiph/stdperiph.h>

#include "atmega328p.h"

using namespace stdperiph;
using namespace stdperiph::timer;

typedef Gpio<PORTB_ADDR, DDRB_ADDR> GpioB;
typedef GpioPinRef<GpioB, 5> led;

//typedef TimerDispatcher<(uint16_t)&TCNT1, 5> TimerBDispathcer;

void ledOn();
void ledOff();
void ledToggle();

int main()
{
	led::mode(BitMode::OUTPUT);
	led::low();

/*	Timer1B::ClockSelect::write(Timer1B::ClockMode::CLK_256);
	
	uint16_t led_on_count = periodToCount(0.5, 256, F_CPU);
	uint16_t led_off_count = led_on_count * 2;

	TimerBDispathcer dispatcher;
	
	dispatcher.setMaxTimerCount(led_off_count);

	TimerHandler ledHandler1;
	ledHandler1.timeout = led_on_count;
	ledHandler1.callback = ledOn;

	TimerHandler ledHandler2;
	ledHandler2.timeout = led_off_count;
	ledHandler2.callback = ledOff;

	dispatcher += &ledHandler1;
	dispatcher += &ledHandler2;*/

	for(;;)
	{
	//	dispatcher.poll();
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

void ledToggle()
{
	led::toggle();
}
