#pragma once

#include "core/TimerWheel.h"
#include "core/types.h"
#include <iostream>
#include <assert.h>
#include <windows.h>
#include <chrono>
#include <time.h>

using namespace core;
using namespace std;

using Tick = unsigned long long;
using TimerEvent = timerwheel::TimerEvent;
using TimerWheel = timerwheel::TimerWheel;
using std::chrono::system_clock;

inline void testTimer()
{
	TimerWheel* wheel = new TimerWheel();
	
	uint64 lastTick = 0;
	TimerEvent* event1 = new TimerEvent(0, 877, 877, [wheel, &lastTick ,event1]() {
		assert(wheel->tick() - lastTick == 877);
		cout << "duration1  " << (lastTick = wheel->tick()) << endl;
	});
	int32 tickCount = 0;
	TimerEvent* event2 = new TimerEvent(0, 7, 7, [wheel, &tickCount]() {
		cout << "duration2  " << wheel->tick() << endl;
		tickCount++;
	}, 100);
	wheel->addTimer(event1);
	//wheel->addTimer(event2);

	int64 maxTick = int64(1) * 1 * 60 * 60 * 1000;
	int64 last = 0;
	int32 count = 0;
	auto start = clock();
	cout << "add begin: "<<"   maxtick: "<< maxTick / (60 * 1000) << "minute" << endl;
	/*for (int64 i = 1; i <= maxTick; i += 997)
	{
		++count;
		TimerEvent* event1 = new TimerEvent(i, i, 0, [i, &last, &count]() {
			cout << i << endl;
			assert(last < i);
			last = i;
			count--;
		});
		wheel->addTimer(event1);
	}*/

	auto finish = clock();
	cout << "add end: "<< count << "   "<< (finish - start) / CLOCKS_PER_SEC<<"seconds" << endl;
	
	{

		// 基于当前系统的当前日期/时间
		time_t now = time(0);
		// 把 now 转换为字符串形式
		char* dt = ctime(&now);
		cout << dt << endl;
	}

	int64 tick = 0;
	while (++tick <= maxTick)
	{
		Sleep(1);
		wheel->update(tick);
	}
	cout << last<< "  "<<tick<< "  "<<count<<"  "<< tickCount << endl;

	{
		// 基于当前系统的当前日期/时间
		time_t now = time(0);
		// 把 now 转换为字符串形式
		char* dt = ctime(&now);
		cout << dt << endl;
	}
}