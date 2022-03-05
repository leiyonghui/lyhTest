#include <iostream>
#include <chrono>
#include "headers.h"
#include <ctime>
#include <iomanip>

void testChrono()
{
	using namespace std;
	using namespace std::chrono;

	// 新纪元1970.1.1时间
	system_clock::time_point epoch;

	duration<int, ratio<60 * 60 * 24>> day(1);
	// 新纪元1970.1.1时间 + 1天
	system_clock::time_point ppt(day);

	using dday = duration<int, ratio<60 * 60 * 24>>;
	// 新纪元1970.1.1时间 + 10天
	time_point<system_clock, dday> t(dday(10));

	// 系统当前时间
	system_clock::time_point today = system_clock::now();

	// 转换为time_t时间类型
	time_t tm ;
	time(&tm);
	cout << "今天的日期是:    " << ctime(&tm);

	time_t tm1 = system_clock::to_time_t(today + day);
	struct std::tm* ptm = std::localtime(&tm1);
	cout << "明天的日期是:    " << std::put_time(std::localtime(&tm1), "%D %R") << endl;

	time_t tm2 = system_clock::to_time_t(epoch);
	cout << "新纪元时间:      " << ctime(&tm2);

	time_t tm3 = system_clock::to_time_t(ppt);
	cout << "新纪元时间+1天:  " << ctime(&tm3);

	time_t tm4 = system_clock::to_time_t(t);
	cout << "新纪元时间+10天: " << ctime(&tm4);

	using namespace std::literals;
	chrono::nanoseconds a = 1ms;
	cout << a.count() <<"  "<< chrono::nanoseconds::period::den <<"  "<< chrono::nanoseconds::period::den / a.count() << endl;

	// 获取开始时间点
	steady_clock::time_point start = steady_clock::now();
	// 执行业务流程
	cout << "print 1000 stars ...." << endl;
	for (int i = 0; i < 1000; ++i)
	{
		cout << "*";
	}
	cout << endl;
	// 获取结束时间点
	steady_clock::time_point last = steady_clock::now();
	// 计算差值
	auto dt = last - start;
	cout << "总共耗时: " << dt.count() << "纳秒" << endl;
}