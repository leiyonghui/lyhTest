#include "TimerWheel.h"

namespace timerwheel
{
	void TimerWheel::addTimer(TimerEvent* event)
	{
		Tick tick = event->_tick - _curTick;
		assert(tick > 0);
		int32 slotindex = 0;
		int32 wheelIndex = 0;
		while (tick >= WHEEL_SIZE)
		{
			tick = tick >> (++slotindex * BIT_SIZE);
		}
		wheelIndex = tick & WHEEL_MASK;
		assert(slotindex < SLOT_SIZE && wheelIndex < WHEEL_SIZE);
		_slot[slotindex][wheelIndex]._slot.pushBack(*event);
	}

	void TimerWheel::delTimer(TimerEvent* event)
	{
		event->leave();
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

	void TimerWheel::_updateSlot(int32 i)
	{
		int32 index = (_curTick >> (i * BIT_SIZE)) & WHEEL_MASK;
		if (index == 0)
		{
			_updateSlot(i+1);
			return;
		}

		auto& slot = _slot[i][index]._slot;
		for (auto iter = slot.begin(); iter != slot.end(); )
		{
			auto event = iter->data();
			iter = iter->next();
			event->leave();
			
            Tick tick = event->_tick - _curTick;
            assert(tick >= 0);
            int32 slotindex = 0;
            int32 wheelIndex = 0;
            while (tick >= WHEEL_SIZE)
            {
                tick = tick >> (++slotindex * BIT_SIZE);
            }
            wheelIndex = tick & WHEEL_MASK;
            assert(slotindex < SLOT_SIZE && wheelIndex < WHEEL_SIZE);
            _slot[slotindex][wheelIndex]._slot.pushBack(*event);
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
			assert(event->_tick <= _curTick);
			try
			{
				event->onTimeout();
				event->leave();
				delete event;
			}
			catch (std::exception e)
			{
				event->leave();
				delete event;
			}
		}
	}

}


