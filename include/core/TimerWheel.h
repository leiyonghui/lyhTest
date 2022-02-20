#pragma once
#include "FastNode.h"
#include <functional>
#include <assert.h>

namespace timerwheel
{
	using int32 = int;
	using int64 = long long;
	using Tick = int64;
	typedef std::function<void()> TimeoutCallback;

	class TimerEvent : CFastNode<TimerEvent*>
	{
		friend class TimerWheel;

		int64 _id;
		Tick _tick;
		Tick _period;
		TimeoutCallback _callback;
	public:
		TimerEvent(int64 id, Tick tick, Tick period, TimeoutCallback callback) : 
			CFastNode<TimerEvent*>(this),
			_id(id),
			_tick(tick),
			_period(period),
			_callback(std::move(callback))
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

	class TimerSolt
	{
		friend class TimerWheel;

		TimerEvent _solt;
	public:
		TimerSolt() : _solt(0, 0, 0, nullptr)
		{

		}
	};

#define WHEEL_SIZE 256
#define BIT_SIZE 8
#define SOLT_SIZE 8
#define WHEEL_MASK 255
#define SOLT_INDEX(n,i) ((uint64(n) >> ((i-1) * 8)) & WHEEL_MASK)

	class TimerWheel
	{
		Tick _curTick;
		Tick _interval;
		Tick _remainder;
		Tick _lasttime;
		TimerSolt _solt[SOLT_SIZE][WHEEL_SIZE];
	public:
		void addTimer(TimerEvent* event);

		void delTimer(TimerEvent* event);

		void _update();

		void update(Tick now);
	};
}
