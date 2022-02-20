#pragma once
#include <unordered_map>
#include <functional>
#include "FastNode.h"

using namespace std;
using int32 = int;
using int64 = long long;
using Tick = int64;

typedef std::function<void()> TimeoutCallback;

template<class T>
class TimerEvent : CFastNode<TimerEvent*>
{
	friend Scheduler<T>;
	friend TimerHander<T>;

	int64 _id;
	TimerHander<T>* _hander;
	Tick _atTick;
	Tick _period;
	TimeoutCallback _callback;
public:
	TimerEvent(int64 id, void* ptr, TimerHander, Tick atTick, Tick period, TimeoutCallback callback) : 
	_id(id),
	_hander(ptr),
	_atTick(atTick),
	_period(period), 
	_callback(std::move(callback)) 
	{
		assert(_hander && _id);
	}

	~TimerEvent()
	{
		assert(_hander);
		//assert(_hander->_timerMap.erase(_id));
	}

	void onTimeout()
	{
		if (_callback)
			_callback();
	}
};

template<class T>
class TimerHander
{
	friend TimerEvent<T>;
	friend Scheduler<T>;

	int64 _nextId;
	unordered_map<int64, TimerEvent<T>*> _timerMap;
	Scheduler<T>* _scheduler;

	TimerHander(const TimerHander&) = delete;
	TimerHander operator=(const TimerHander&) = delete;
public:
	TimerHander(Scheduler<T>* scheduler): _nextId(0),_scheduler(scheduler){}

	~TimerHander()
	{
		cancel();
	}

	int64 addTimer(Tick delay, Tick duration, TimeoutCallback callback)
	{
		int64 id = nextId();
		auto event = _scheduler->addTimer(id, delay, duration, std::forward(callback));
		if (event)
		{
			_timerMap.insert({id, event});
			return id;
		}
		return 0;
	}

	bool cancel(int64 id)
	{
		auto iter = _timerMap.find(id);
		if (iter == _timerMap.end())
		{
			return false;
		}
		_scheduler->delTimer(event);
	}

	void cancel()
	{
		auto iter = _timerMap.begin();
		while (iter != _timerMap.end())
		{
			_scheduler->delTimer(iter->first);
		}
	}

	int64 nextId()
	{
		while (++_nextId)
		{
			if (_nextId && (int)_timerMap.count(_nextId) == 0)
			{
				return _nextId;
			}
		}
	}
};

template<class T>
class Scheduler
{
	T* _cheduler;
public:
	Scheduler(T* cheduler): _cheduler(cheduler){}

	void update(Tick now)
	{
		_cheduler->update(now);
	}

	TimerEvent* addTimer(int64 id, Tick delay, Tick duration, TimeoutCallback callback)
	{
		TimerEvent<T>* event = new TimerEvent<T>(id, delay, duration, std::forward(callback));
		_cheduler->addTimer(event);
		return event;
	}

	bool delTimer(TimerEvent* event)
	{
		_cheduler->delTimer(event);
		delete event;
	}
};