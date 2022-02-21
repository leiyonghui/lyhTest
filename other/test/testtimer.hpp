#pragma once

#include "core/TimerWheel.h"
#include "core/types.h"
#include <iostream>
#include <windows.h>

using namespace core;
using namespace std;

using TimerEvent = timerwheel::TimerEvent;
using TimerWheel = timerwheel::TimerWheel;
using Tick = int64;

inline void testTimer()
{
	TimerWheel* wheel = new TimerWheel();
	
	int32 maxTick = 3000;
	for (int32 i = 1; i<= maxTick; i++)
	{
		TimerEvent* event1 = new TimerEvent(1, i, 1, [i]() {
			cout << i << endl;
		});
		wheel->addTimer(event1);
	}

	int64 tick = 0;
	while (++tick <= maxTick)
	{
		Sleep(1000);
		cout << "--- "<<tick <<" ---" << endl;
		wheel->update(tick);
	}
}