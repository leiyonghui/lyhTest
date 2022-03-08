#pragma once
/*(https://www.eet-china.com/mp/a74844.html)

time_t:
��Ȼ��׼��û�и������壬���Ǹ����ͼ��������������ͣ���ʾ�� 1970 �� 1 �� 1 �� 00:00 UTC �������������������������룩����Ӧ POSIX ʱ�䡣

tm:
���в�ֵ���ֵ��������ں�ʱ��Ľṹ��

std::ratio:
��ʾÿ��ʱ�����ڵ����������е�һ��ģ����� Num ������ӣ�Denom �����ĸ��
�÷�ĸֵĬ��Ϊ 1����ˣ�ratio �������һ�����ӳ��Է�ĸ����ֵ�����磺ratio<2> ����һ��ʱ�������� 2 �룬
ratio<60 > ����һ���ӣ�ratio<60 * 60 > ����һ��Сʱ��ratio<60 * 60 * 24 > ����һ�졣
�� ratio<1, 1000 > ������� 1 / 1000 �룬Ҳ���� 1 ���룬ratio<1, 1000000 > ����һ΢�룬ratio<1, 1000000000 > ����һ���롣

std:system_clock:
��ʾϵͳ��Χ��ʵʱ���ӡ�
�����Բ������������ϵͳ�ϣ�ϵͳʱ��������κ�ʱ�򱻵��ڡ�����Ψһ������ӳ����ʱ��㵽 C ���ʱ��� C++ ʱ��
��ָ�� system_clock �ļ�Ԫ��������ʵ��ʹ�� Unix ʱ�䣨����Э������ʱ (UTC) 1970 �� 1 �� 1 �������� 00:00:00 ��ʼ��ʱ�䣬�������룩��(C++20 ǰ)
system_clock ���� Unix ʱ�䣨����Э������ʱ (UTC) 1970 �� 1 �� 1 �������� 00:00:00 ��ʼ��ʱ�䣬�������룩��(C++20)

std::chrono::steady_clock:
��ʾ����ʱ�ӡ���ʱ�ӵ�ʱ����޷����٣���Ϊ����ʱ����ǰ�ƶ�����ʱ�������ʱ���޹أ����磬�������ϴ�������ʼ��ʱ�䣩���������ڶ��������

std::chrono::duration:
template<
	class Rep,
	class Period = std::ratio<1>
> class duration;
��ʾʱ������
���� Rep ���͵ļƴ����ͼƴ�������ɣ����мƴ�������һ����������������������ʾ��һ���ƴε���һ����������
�洢�� duration �����ݽ��� Rep ���͵ļƴ������� Rep �Ǹ��������� duration �ܱ�ʾС���ļƴ����� Period ������Ϊʱ�����͵�һ���֣���ֻ�ڲ�ͬʱ����ת��ʱʹ�á�

std::chrono::time_point:
��ģ�� std::chrono::time_point ��ʾʱ���е�һ���㡣����ʵ�ֳ���ͬ�洢һ�� Duration ���͵��� Clock �ļ�Ԫ��ʼ��ʼ��ʱ������ֵ��
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
		return time(NULL);//���ر��дӼ�Ԫ��ʼ������������������ֵ
#else
		return system_clock::to_time_t(system_clock::now());//ת��ϵͳʱ��ʱ���Ϊ std::time_t
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

	std::map<std::string, uint64> _aveTime;  // ƽ��ʱ��
	std::map<std::string, uint64> _maxTicks;
};