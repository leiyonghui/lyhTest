#include "Timers.h"

TimerEvent::~TimerEvent()
{
	assert(_hander->_timerMap.erase(_id));
}

int64 TimerHander::addTimer(Tick delay, Tick duration, int32 count, TimeoutCallback callback)
{
	int64 id = nextId();
	TimerEvent* event = new TimerEvent(id, this, delay, duration, count, callback);
	_scheduler->addTimer(event);
	_timerMap[id] = event;
	return 0;
}

bool TimerHander::cancel(int64 id)
{
	auto iter = _timerMap.find(id);
	if (iter == _timerMap.end())
	{
		return false;
	}
	_scheduler->delTimer(iter->second);
	return true;
}

void TimerHander::cancel()
{
	auto iter = _timerMap.begin();
	while (iter != _timerMap.end())
	{
		_scheduler->delTimer(iter->second);
	}
}

