
#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

#include "stdperiph/bitref.h"
#include "stdperiph/bitgroup.h"

/* Timer 1 Control Register A */

namespace Timer1A
{
	enum { PERIPH = ((uint16_t)&TCCR1A) };

	typedef stdperiph::BitGroup<PERIPH, 6, 2> COM1A; ///< Compare output for channel A
	typedef stdperiph::BitGroup<PERIPH, 4, 2> COM1B; ///< Compare output for channel B

	typedef stdperiph::BitGroup<PERIPH, 0, 2> WGM; ///< Wave mode

	namespace CompareOutputMode
	{
		enum
		{
			NORMAL = 0x00,
			TOGGLE = 0x01,
			CLEAR  = 0x02,
			SET    = 0x03
		};
	}

	namespace CompareOutputModeFastPWN
	{
		enum
		{
			NORMAL = 0x00,
			MODE1  = 0x01,
			MODE2  = 0x02,
			MODE3  = 0x03
		};
	}

	namespace CompareOutputModePhaseCorrect
	{
		enum
		{
			NORMAL = 0x00,
			MODE1  = 1,
			MODE2  = 2,
			MODE3  = 3
		};
	}
}

/* Timer 1 Control Register B */

namespace Timer1B
{
	enum{ PERIPH = ((uint16_t)&TCCR1B) };

	typedef stdperiph::BitRef<PERIPH, 7>      ICNC; ///< Input capture noise canceler 
	typedef stdperiph::BitRef<PERIPH, 6>      ICES; ///< Input capture edge select

	typedef stdperiph::BitGroup<PERIPH, 3, 2> WGM;   ///< Wave generator mode

	typedef stdperiph::BitGroup<PERIPH, 0, 3> ClockSelect;   ///< Clock select

	namespace ClockMode
	{
		enum
		{
			NO_CLK       = 0,
			CLK_1        = 1,
			CLK_8        = 2,
			CLK_64       = 3,
			CLK_256      = 4,
			CLK_1024     = 5,
			CLK_EXT_FALL = 6,
			CLK_EXT_RISE = 7
		};
	};
}

namespace TimerInterruptMask
{
	enum{ PERIPH = ((uint16_t)&TIMSK1) };

	typedef stdperiph::BitRef<PERIPH, 5> InputCapture;
	typedef stdperiph::BitRef<PERIPH, 2> OutputCapture1B;
	typedef stdperiph::BitRef<PERIPH, 1> OutputCapture1A;
	typedef stdperiph::BitRef<PERIPH, 0> Overflow;
}


#endif // TIMER_H
