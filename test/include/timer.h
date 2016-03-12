
#ifndef TIMER_H
#define TIMER_H

#include "config/portmap_328p.h"
#include "stdperiph/bitref.h"
#include "stdperiph/bitgroup.h"



template<int TIMER_ADDR>
struct Timer
{
	typedef stdperiph::BitRef<TIMER_ADDR, 7> input_capture_noise_canceler;
	typedef stdperiph::BitRef<TIMER_ADDR, 6> input_capture_edge_select;

	typedef stdperiph::BitGroup<TIMER_ADDR, 3, 2> wave_mode;

	typedef stdperiph::BitGroup<TIMER_ADDR, 0, 3> clock_select;

	struct clock_mode
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
};




#endif // TIMER_H
