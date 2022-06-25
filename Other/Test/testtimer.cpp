#pragma once
#include "core/Configs.h"
#include "core/TimeHelp.h"
#include "core/Timers.h"
#include "core/TimerWheel.h"
#include "core/TimerSet.h"
#include <iostream>
#include <assert.h>
#include <windows.h>
#include <chrono>
#include <time.h>
#include <map>
#include <algorithm>
#include "core/TimerImpl.h"

using namespace core;
using namespace std;

using Tick = unsigned long long;
using TimerWheel = timerwheel::TimerWheel;
using TimerSet = timerset::TimerSet;
using std::chrono::system_clock;
using namespace std::literals;

void testTimer()
{
    int64 id = 0;
    std::map<int32, TimerEvent*> Map;
//#define WHELL
#ifdef WHELL
	TimerWheel* wheel = new TimerWheel();
#else
	TimerSet* wheel = new TimerSet();
#endif
    
    int64 maxTick = int64(1) * 24 * 60 * 60 * 1000;
    auto start = clock();
    cout << "add begin: " << "   maxtick: " << maxTick / (60 * 1000) << "minute" << endl;

    uint64 lastTick = 0;
    id++;
    TimerEvent* event1 = new TimerEvent(id, nullptr, uint64(887), uint64(887), 1, [wheel, id, &lastTick, &Map]() {
        auto event = Map[id];
        assert(lastTick <= event->tick());
        lastTick = event->tick();
    }, false);
    Map[id] = event1;
    id++;
    TimerEvent* event2 = new TimerEvent(id, NULL, 7, 7, 100, [wheel, &Map, id, &lastTick]() {
        //cout << "duration2  " << wheel->tick() << endl;
        auto event = Map[id];
        assert(lastTick <= event->tick());
        lastTick = event->tick();
    }, false);
    Map[id] = event2;
    wheel->addTimer(event1);
    wheel->addTimer(event2);

    for (int32 i = 1; i < 12000; i+= 347)
    {
        id++;
        TimerEvent* event = new TimerEvent(id, NULL, i, i, 1, [wheel, i, id, &Map, &lastTick]() {
            
            auto event = Map[id];
            assert(lastTick <= event->tick());
            lastTick = event->tick();

        }, false);
        wheel->addTimer(event);
        Map[id] = event;
    }

    int64 last = 0;
    for (int64 i = 1; i <= maxTick; i += 997)
    {
        ++id;
        TimerEvent* event1 = new TimerEvent(id, NULL, i, 0, 1, [i, &last, id, &Map, &lastTick]() {

            assert(i - last == 997 || i == 1);
            last = i;

            auto event = Map[id];
            assert(lastTick <= event->tick());
            lastTick = event->tick();


        }, false);
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
    //cout << "totalEvent: " << TimerEvent::TotalEvent << endl;
    while (++tick <= maxTick)
    {
        uint64 start = clock();
        wheel->update(tick);
        uint64 finish = clock();
        uint64 value = finish - start;
        sum += value;
        maxv = value > maxv ? value : maxv;
#ifdef WHELL
        if (expend < wheel->expend())
        {
            expend = max(expend, wheel->expend());
            executeExpend = wheel->executeCount();
        }
        executeCount = max(executeCount, wheel->executeCount());
#endif // WHELL
    }
    cout << "sum:"<<sum
        <<"  ave: "<< sum/tick
        <<"  max: "<< maxv 
        <<"  expend: "<< expend 
        <<"  expendEx: "<< executeExpend 
        <<"  maxExecute: "<< executeCount 
    << endl;

	//cout << "totalEvent: " << TimerEvent::TotalEvent << endl;

    {
        // 基于当前系统的当前日期/时间
        time_t now = time(0);
        // 把 now 转换为字符串形式
        char* dt = ctime(&now);
        cout << dt << endl;
    }
}

void NOW(string str)
{
    std::cout << str <<" time:"<< TimeHelp::TimeToString(TimeHelp::now_time())<< "   clock:"<< TimeHelp::ns2ms(TimeHelp::clock()).count() << endl;
}

void testTimer2()
{
#ifdef WHELL
	TimerWheel* wheel = new TimerWheel();
#else
    TimerSet* wheel = new TimerSet();
#endif
	TimerHander* hander = new TimerHander(wheel);


    CheckTime check;
    check.CheckBegin();

    auto now = system_clock::now();
	int64 id;
    int32 sum = 0;
	TimeHelp::StartUp();
    id = hander->addTimer(100ms, 1000ms, 5, [hander, &id, &sum]() {
        sum++;
        if (sum == 3)
        {
		    hander->cancel(id);
        }
        NOW("----time1");
    });
	auto t = std::bind(NOW, _1);
	t("");
	//hander->addTimer(1ms, 0ms, 5, std::bind(NOW));

    int32 tick = 0, maxTick = 7 * 1000;
    while (++tick <= maxTick)
    {
        Sleep(1);
        auto now = TimeHelp::clock();
        wheel->update(now.count());
    }
    //cout << TimerEvent::TotalEvent << endl;
    check.CheckPoint("1");
}

class Object : public std::enable_shared_from_this<Object>, public TimerImpl<Object>
{
public:
	Object(IScheduler* s, int32 v) : TimerImpl<Object>(s), _v(v) {}

	~Object()
	{
		_v = 0;
	}

	int32 _v;
};

std::shared_ptr<Object> OBJ;
#include <algorithm>
#include <random>
void testTimer3()
{
	TimerSet* wheel = new TimerSet();
	OBJ = std::make_shared<Object>(wheel, 3);
	OBJ->startTimer(100ms, 100ms, [](std::shared_ptr<Object> ptr) {
		cout << ptr->_v << "   "<< TimeHelp::clock().count() << endl;
	});
    std::vector<int64> ids;
    for (int32 i = 1; i <= 1000; i++)
    {
        ids.push_back(OBJ->startTimer(1ms * i, i % 2 ? 1ms * 2 : 0ms, [i](std::shared_ptr<Object> ptr) {
            cout << " - " << i << endl;
         }));
    }
    std::shuffle(ids.begin(), ids.end(), std::random_device());

	TimeHelp::StartUp();

	
	int32 tick = 0, maxTick = 70 * 1000;
	while (++tick <= maxTick)
	{
		Sleep(1);
		if (tick == 3000) 
		{
			//obj = nullptr;
			cout << " ------ " << endl;
		}
		auto now = TimeHelp::clock();
		wheel->update(now.count());
        if (tick % 10 == 1 && !ids.empty())
        {
			auto id = ids.back();
			ids.pop_back();
			cout << " stop :" << id << "  " << OBJ->stopTimer(id) << endl;
        }
        if (tick > 50000)
        {
			OBJ = nullptr;
			cout << " ddd " << endl;
        }
		
	}

}