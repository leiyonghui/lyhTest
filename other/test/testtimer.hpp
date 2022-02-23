#pragma once

#include "core/TimerWheel.h"
#include "core/types.h"
#include <iostream>
#include <assert.h>
#include <windows.h>
#include <chrono>
#include <time.h>
#include <map>
#include <algorithm>

using namespace core;
using namespace std;

using Tick = unsigned long long;
using TimerEvent = timerwheel::TimerEvent;
using TimerWheel = timerwheel::TimerWheel;
using std::chrono::system_clock;

inline void testTimer()
{
    int32 id = 0;
    std::map<int32, TimerEvent*> Map;
    TimerWheel* wheel = new TimerWheel();
    
    int64 maxTick = int64(1) * 24 * 60 * 60 * 1000;
    auto start = clock();
    cout << "add begin: " << "   maxtick: " << maxTick / (60 * 1000) << "minute" << endl;

    uint64 lastTick = 0;
    TimerEvent* event1 = new TimerEvent(++id, 877, 877, [wheel, id, &lastTick, &Map]() {
        auto event = Map[id];
        assert(lastTick <= event->tick());
        lastTick = event->tick();
    });
    Map[id] = event1;
    TimerEvent* event2 = new TimerEvent(++id, 7, 7, [wheel, &Map, id, &lastTick]() {
        //cout << "duration2  " << wheel->tick() << endl;
        auto event = Map[id];
        assert(lastTick <= event->tick());
        lastTick = event->tick();
    }, 100);
    Map[id] = event2;
    wheel->addTimer(event1);
    wheel->addTimer(event2);

    for (int32 i = 1; i < 12000; i+= 347)
    {
        TimerEvent* event = new TimerEvent(++id, i, i, [wheel, i, id, &Map, &lastTick]() {
            
            auto event = Map[id];
            assert(lastTick <= event->tick());
            lastTick = event->tick();

        });
        wheel->addTimer(event);
        Map[id] = event;
    }

    int64 last = 0;
    for (int64 i = 1; i <= maxTick; i += 997)
    {
        TimerEvent* event1 = new TimerEvent(++id, i, 0, [i, &last, id, &Map, &lastTick]() {

            assert(i - last == 997 || i == 1);
            last = i;

            auto event = Map[id];
            assert(lastTick <= event->tick());
            lastTick = event->tick();
        });
        Map[id] = event1;
        wheel->addTimer(event1);
    }

    auto finish = clock();
    cout << "add end: "<< (finish - start) / CLOCKS_PER_SEC<<" seconds" << "  event: "<< Map.size() << endl;
    
    {

        // 基于当前系统的当前日期/时间
        time_t now = time(0);
        // 把 now 转换为字符串形式
        char* dt = ctime(&now);
        cout << dt << endl;
    }

    int64 tick = 0;
    uint64 sum = 0;
    uint64 maxv = 0;
    uint64 expend = 0;
    uint64 executeCount = 0;
    uint64 executeExpend = 0;
    while (++tick <= maxTick)
    {
        uint64 start = clock();
        wheel->update(tick);
        uint64 finish = clock();
        uint64 value = finish - start;
        sum += value;
        maxv = value > maxv ? value : maxv;
        if (expend < wheel->expend()) 
        {
            expend = max(expend, wheel->expend());
            executeExpend = wheel->executeCount();
        }
        executeCount = max(executeCount, wheel->executeCount());
    }
    cout << "sum:"<<sum
        <<"  ave: "<< sum/tick
        <<"  max: "<< maxv 
        <<"  expend: "<< expend 
        <<"  expendEx: "<< executeExpend 
        <<"  maxExecute: "<< executeCount 
    << endl;

    {
        // 基于当前系统的当前日期/时间
        time_t now = time(0);
        // 把 now 转换为字符串形式
        char* dt = ctime(&now);
        cout << dt << endl;
    }
}