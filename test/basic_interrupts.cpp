
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdperiph/stdperiph.h>

#include "config/portmap_328p.h"
//#include "timer.h"

using namespace stdperiph;
using namespace stdperiph::timer;

typedef Gpio<PORTB_ADDR, DDRB_ADDR> GpioB;
typedef GpioPinRef<GpioB, 5> led;

int main()
{
/*	led::mode(BitMode::OUTPUT);
	led::low();

    // set up timer with prescaler = 64 and CTC mode
    Timer1B::ClockSelect::write(Timer1B::ClockMode::CLK_64);
    TCCR1B |= (1 << WGM12);
  
    // initialize counter
    TCNT1 = 0;
  
    // initialize compare value
    OCR1A = 24999;
  
    // enable compare interrupt
    TimerInterruptMask::OutputCapture1A::high();

	sei();*/

	for(;;);

	return 0;
}

ISR(TIMER1_COMPA_vect)
{
	led::toggle();
}
