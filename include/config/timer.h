
#ifndef TIMER_H
#define TIMER_H

#include "config/portmap_328p.h"
#include "perph/bitref.h"
#include "perph/bitgroup.h"

/*

	Target Timer Count = (1 / Target Frequency) / (Prescale / Input Frequency) - 1

*/

/*
namespace timerb
{
	typedef perph::BitRef<TIMERB_ADDR, 7> input_capture_noise_canceler;
	typedef perph::BitRef<TIMERB_ADDR, 6> input_capture_edge_select;

	typedef perph::BitGroup<TIMERB_ADDR, 3, 2> wave_mode;

	typedef perph::BitGroup<TIMERB_ADDR, 0, 3> clock_select;

	namespace clock_mode
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
	}
}
*/


template<int TIMER_ADDR>
struct Timer
{
	typedef perph::BitRef<TIMER_ADDR, 7> input_capture_noise_canceler;
	typedef perph::BitRef<TIMER_ADDR, 6> input_capture_edge_select;

	typedef perph::BitGroup<TIMER_ADDR, 3, 2> wave_mode;

	typedef perph::BitGroup<TIMER_ADDR, 0, 3> clock_select;

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

template<int TIMER_COUNT_REG, int BUFFER_SIZE>
class TimerCallback
{
private:
	typedef void (*Callback)(void);

public:
	TimerCallback() : num_callbacks_(0)
	{

	}

	void poll()
	{
		if(TCNT1 >= 31249)
		{
			for(int i = 0; i < num_callbacks_; ++i)
			{
				delegate_[i]();
			}
		}
	}

	void operator+=(Callback callback)
	{
		delegate_[num_callbacks_++] = callback;
	}

private:
	Callback delegate_[BUFFER_SIZE];
	uint16_t num_callbacks_;
};


#endif // TIMER_H
