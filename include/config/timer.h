
#ifndef TIMER_H
#define TIMER_H

#include "config/portmap_328p.h"
#include "perph/pinref.h"

namespace timerb
{
	typedef PinRef<TIMERB_ADDR, 7> input_capture_noise_canceler;
}

#endif // TIMER_H
