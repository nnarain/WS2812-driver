
#ifndef TIMER_H
#define TIMER_H

#include "config/portmap_328p.h"
#include "stdperiph/bitref.h"
#include "stdperiph/bitgroup.h"

/*

	Target Timer Count = (1 / Target Frequency) / (Prescale / Input Frequency) - 1

*/



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

typedef void (*Callback)(void);

struct TimerHandler
{
	uint16_t timeout;
	Callback callback;
};

template<int TIMER_COUNT_REG, int BUFFER_SIZE>
class TimerDispatcher
{
private:
	typedef void (*Callback)(void);

public:
	TimerDispatcher() : 
		num_handlers_(0),
		max_timer_count_(UINT16_MAX)
	{

	}

	void poll()
	{
		for(int i = 0; i < num_handlers_; ++i)
		{
			TimerHandler * handler = handlers_[i];

			if(TCNT1 >= handler->timeout)
			{
				handler->callback();
			}
		}

		if(IO_PORT16(TIMER_COUNT_REG) >= max_timer_count_)
		{
			IO_PORT16(TIMER_COUNT_REG) = 0;
		}
	}

	void operator+=(TimerHandler * handler)
	{
		handlers_[num_handlers_++] = handler;
	}

	void setMaxTimerCount(uint16_t max)
	{
		max_timer_count_ = max;
	}

private:
	TimerHandler *handlers_[BUFFER_SIZE];
	uint16_t num_handlers_;
	uint16_t max_timer_count_;
};


#endif // TIMER_H
