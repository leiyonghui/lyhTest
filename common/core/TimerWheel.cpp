#include "TimerWheel.h"

namespace timerwheel
{
	void TimerWheel::addTimer(TimerEvent* event)
	{
		Tick tick = _curTick - event->_tick;
		int32 soltindex = 0;
		int32 wheelIndex = 0;
		while (tick >= WHEEL_SIZE)
		{
			tick = tick >> (++soltindex * BIT_SIZE);
		}
		wheelIndex = tick & WHEEL_MASK;
		assert(soltindex < SOLT_SIZE && wheelIndex < WHEEL_SIZE);
		_solt[soltindex][wheelIndex]._solt.pushBack(*event);
	}

	void TimerWheel::delTimer(TimerEvent* event)
	{
		event->leave();
	}

	void TimerWheel::_update()
	{

	}

	void TimerWheel::update(Tick now)
	{
		if (now > _lasttime)
		{
			Tick diff = now - _lasttime + _remainder;
			while (diff > _interval)
			{
				diff -= _interval;
				_update();
			}
			_remainder = diff;
		}
	}
}


