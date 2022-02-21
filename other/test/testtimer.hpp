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

using Tick = int64;
using TimerEvent = timerwheel::TimerEvent;
using TimerWheel = timerwheel::TimerWheel;
using std::chrono::system_clock;

inline void testTimer()
{
	TimerWheel* wheel = new TimerWheel();
	
	int64 maxTick = int64(1) * 10 * 60 * 60 * 1000;
	int64 last = 0;
	int32 count = 0;
	auto start = clock();
	cout << "add begin: "<<"   maxtick: "<< maxTick / (60 * 1000) << "minute" << endl;
	for (int64 i = 1; i <= maxTick; i += 331)
	{
		++count;
		TimerEvent* event1 = new TimerEvent(i, i, 1, [i, &last, &count]() {
			cout << i << endl;
			assert(last < i);
			last = i;
			count--;
		});
		wheel->addTimer(event1);
	}

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
	cout << last<< "  "<<tick<< "  "<<count << endl;

	{
		// 基于当前系统的当前日期/时间
		time_t now = time(0);
		// 把 now 转换为字符串形式
		char* dt = ctime(&now);
		cout << dt << endl;
	}
}