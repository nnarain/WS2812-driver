
#ifndef STDPERIPH_TIMER_H
#define STDPERIPH_TIMER_H

/*

	Target Timer Count = (1 / Target Frequency) / (Prescale / Input Frequency) - 1

*/

namespace stdperiph
{
namespace timer
{

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
	
}
}

#endif
