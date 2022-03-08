#pragma once
/*(https://www.eet-china.com/mp/a74844.html)

time_t:
虽然标准中没有给出定义，但是该类型几乎总是整数类型，表示自 1970 年 1 月 1 日 00:00 UTC 以来所经过的秒数（不计闰秒），对应 POSIX 时间。

tm:
保有拆分到组分的日历日期和时间的结构体

std::ratio:
表示每个时钟周期的秒数，其中第一个模板参数 Num 代表分子，Denom 代表分母，
该分母值默认为 1，因此，ratio 代表的是一个分子除以分母的数值，比如：ratio<2> 代表一个时钟周期是 2 秒，
ratio<60 > 代表一分钟，ratio<60 * 60 > 代表一个小时，ratio<60 * 60 * 24 > 代表一天。
而 ratio<1, 1000 > 代表的是 1 / 1000 秒，也就是 1 毫秒，ratio<1, 1000000 > 代表一微秒，ratio<1, 1000000000 > 代表一纳秒。

std:system_clock:
表示系统范围的实时壁钟。
它可以不单调：大多数系统上，系统时间可以在任何时候被调节。它是唯一有能力映射其时间点到 C 风格时间的 C++ 时钟
不指定 system_clock 的纪元，但多数实现使用 Unix 时间（即从协调世界时 (UTC) 1970 年 1 月 1 日星期四 00:00:00 开始的时间，不计闰秒）。(C++20 前)
system_clock 度量 Unix 时间（即从协调世界时 (UTC) 1970 年 1 月 1 日星期四 00:00:00 开始的时间，不计闰秒）。(C++20)

std::chrono::steady_clock:
表示单调时钟。此时钟的时间点无法减少，因为物理时间向前移动。此时钟与壁钟时间无关（例如，它能是上次重启开始的时间），且最适于度量间隔。

std::chrono::duration:
template<
	class Rep,
	class Period = std::ratio<1>
> class duration;
表示时间间隔。
它由 Rep 类型的计次数和计次周期组成，其中计次周期是一个编译期有理数常量，表示从一个计次到下一个的秒数。
存储于 duration 的数据仅有 Rep 类型的计次数。若 Rep 是浮点数，则 duration 能表示小数的计次数。 Period 被包含为时长类型的一部分，且只在不同时长间转换时使用。

std::chrono::time_point:
类模板 std::chrono::time_point 表示时间中的一个点。它被实现成如同存储一个 Duration 类型的自 Clock 的纪元起始开始的时间间隔的值。
*/

#include <chrono>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>

class TimeHelp
{
public:
	using system_clock = std::chrono::system_clock;
	using steady_clock = std::chrono::steady_clock;

	static int GetYear(time_t t);

	static int GetMonth(time_t t);

	static int GetDay(time_t t);

	static int GetHour(time_t t);

	static int GetMinute(time_t t);

	static int GetSecond(time_t t);

	static time_t now() {
#if 0
		return time(NULL);//返回保有从纪元开始至今秒数的整数类型值
#else
		return system_clock::to_time_t(system_clock::now());//转换系统时钟时间点为 std::time_t
#endif
	};

	static std::chrono::nanoseconds clock() {
		return steady_clock::now() - START_CLOCK;
	};

	static std::chrono::milliseconds ns2ms(const std::chrono::nanoseconds& ns) {
		return std::chrono::duration_cast<std::chrono::milliseconds>(ns);
	}

	static std::chrono::milliseconds clock_ms() {
		return ns2ms(clock());
	}

	static std::string TimeToString(time_t t);

	static void StartUp();

private:
	static std::chrono::time_point<steady_clock> START_CLOCK;
};

class CheckTime
{
public:
	using uint64 = unsigned long long;

	void CheckBegin();
	void CheckPoint(std::string key);

private:
	uint64 _beginTick;

	std::map<std::string, uint64> _aveTime;  // 平均时间
	std::map<std::string, uint64> _maxTicks;
};