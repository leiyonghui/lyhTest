#pragma once

#include "core/TimerWheel.h"
#include "core/types.h"
#include <iostream>
#include <assert.h>
#include <windows.h>

using namespace core;
using namespace std;

using TimerEvent = timerwheel::TimerEvent;
using TimerWheel = timerwheel::TimerWheel;
using Tick = int64;

inline void testTimer()
{
	TimerWheel* wheel = new TimerWheel();
	
	int64 maxTick = int64(1) * 3 * 60 * 60 * 1000;
	int64 last = 0;
	cout << "begin: "<<maxTick << endl;
	for (int64 i = 1; i<= maxTick; i++)
	{
		TimerEvent* event1 = new TimerEvent(i, i, 1, [i, &last]() {
			cout << i << endl;
			assert(last < i);
			last = i;
		});
		wheel->addTimer(event1);
	}
	cout << "end: " << endl;
	int64 tick = 0;
	while (++tick <= maxTick)
	{
		//Sleep(1);
		cout << "--- "<<tick <<" ---" << endl;
		wheel->update(tick);
	}
	cout << last<< "  "<<tick << endl;
}