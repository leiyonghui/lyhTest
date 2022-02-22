#include "TimerWheel.h"
#include <iostream>

namespace timerwheel
{
	void TimerWheel::addTimer(TimerEvent* event)
	{
		Tick tick = event->_tick - _curTick;
		assert(tick > 0);
		_addTimer(event);
	}

	void TimerWheel::delTimer(TimerEvent* event)
	{
		event->leave();
		delete event;
	}

	void TimerWheel::update(Tick now)
	{
		if (now > _lasttime)
		{
			Tick diff = now - _lasttime + _remainder;
			_lasttime = now;
			while (diff >= _interval)
			{
				diff -= _interval;
				_update();
			}
			_remainder = diff;
		}
	}

	void TimerWheel::_onTimeout(TimerEvent* event)
	{
		assert(event->_tick <= _curTick);
		try
		{
			event->onTimeout();
			if (event->_period > 0 && (event->_count > 1 || !event->_count))
			{
				if (event->_count)
					event->_count--;
				event->_tick += event->_period;
				_addTimer(event);
			}
			else
			{
				delete event;
			}
		}
		catch (std::exception e)
		{
			event->leave();
			delete event;

			std::cout << e.what() << std::endl;
		}
	}

	void TimerWheel::_addTimer(TimerEvent* event)
	{
		Tick tick = event->_tick - _curTick;
		assert(tick >= 0);
		int32 slotindex = 0;
		int32 wheelIndex = 0;
		while (tick >= WHEEL_SIZE)
		{
			slotindex++;
			tick = tick >> BIT_SIZE;
		}
		wheelIndex = (tick + SLOT_INDEX(_curTick, slotindex)) & WHEEL_MASK;
		assert(slotindex < SLOT_SIZE && wheelIndex < WHEEL_SIZE);
		_slot[slotindex][wheelIndex]._slot.pushBack(*event);
	}

	void TimerWheel::_updateSlot(int32 i)
	{
		int32 index = SLOT_INDEX(_curTick, i);
		if (index == 0)
		{
			if (i+1 < SLOT_SIZE)
				_updateSlot(i+1);
			return;
		}

		auto& slot = _slot[i][index]._slot;
		for (auto iter = slot.begin(); iter != slot.end(); )
		{
			auto event = iter->data();
			iter = iter->next();
			event->leave();
			if (event->_tick <= _curTick)
				_onTimeout(event);
			else
				_addTimer(event);
		}
	}

	void TimerWheel::_update()
	{
		++_curTick;

		int32 index = _curTick & WHEEL_MASK;
		if (index == 0)
			_updateSlot(1);
		
		auto& slot = _slot[0][index]._slot;
		for (auto iter = slot.begin(); iter != slot.end(); )
		{
			auto event = iter->data();
			iter = iter->next();
			event->leave();
			_onTimeout(event);
		}
	}

}


