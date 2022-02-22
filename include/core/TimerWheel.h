#pragma once
#include "FastNode.h"
#include <functional>
#include <assert.h>

namespace timerwheel
{
	using int32 = int;
	using int64 = long long;
	using uint64 = unsigned long long;
	using Tick = uint64;
	typedef std::function<void()> TimeoutCallback;

	class TimerEvent : CFastNode<TimerEvent*>
	{
		friend class TimerWheel;

		int64 _id;
		Tick _tick;
		Tick _period;
		TimeoutCallback _callback;
		int32 _count;
	public:
		TimerEvent(int64 id, Tick tick, Tick period, TimeoutCallback callback, int32 count = 0) : 
			CFastNode<TimerEvent*>(this),
			_id(id),
			_tick(tick),
			_period(period),
			_callback(std::move(callback)),
			_count(count)
		{

		}

		~TimerEvent()
		{
			
		}

		void onTimeout()
		{
			if (_callback)
				_callback();
		}
	};

	class TimerSlot
	{
		friend class TimerWheel;

		TimerEvent _slot;
	public:
		TimerSlot() : _slot(0, 0, 0, nullptr)
		{

		}
	};

#define WHEEL_SIZE 256
#define BIT_SIZE 8
#define SLOT_SIZE 8
#define WHEEL_MASK 255
#define SLOT_INDEX(n,i) ((uint64(n) >> (i * 8)) & WHEEL_MASK)

	class TimerWheel
	{
		Tick _curTick;
		Tick _interval;
		Tick _remainder;
		Tick _lasttime;
		TimerSlot _slot[SLOT_SIZE][WHEEL_SIZE];
	public:
		TimerWheel(Tick interval = 1) : _curTick(0), _interval(interval), _remainder(0), _lasttime(0)
		{

		}

		Tick tick() { return _curTick; };

		void addTimer(TimerEvent* event);

		void delTimer(TimerEvent* event);

		void update(Tick now);

	private:
		void _onTimeout(TimerEvent* event);

		void _addTimer(TimerEvent* event);

		void _updateSlot(int32 i);

		void _update();
	};
}
