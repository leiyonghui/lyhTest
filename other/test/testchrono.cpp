#include <iostream>
#include <chrono>
#include "headers.h"
#include <ctime>
#include <iomanip>

void testChrono()
{
	using namespace std;
	using namespace std::chrono;

	// �¼�Ԫ1970.1.1ʱ��
	system_clock::time_point epoch;

	duration<int, ratio<60 * 60 * 24>> day(1);
	// �¼�Ԫ1970.1.1ʱ�� + 1��
	system_clock::time_point ppt(day);

	using dday = duration<int, ratio<60 * 60 * 24>>;
	// �¼�Ԫ1970.1.1ʱ�� + 10��
	time_point<system_clock, dday> t(dday(10));

	// ϵͳ��ǰʱ��
	system_clock::time_point today = system_clock::now();

	// ת��Ϊtime_tʱ������
	time_t tm ;
	time(&tm);
	cout << "�����������:    " << ctime(&tm);

	time_t tm1 = system_clock::to_time_t(today + day);
	struct std::tm* ptm = std::localtime(&tm1);
	cout << "�����������:    " << std::put_time(std::localtime(&tm1), "%D %R") << endl;

	time_t tm2 = system_clock::to_time_t(epoch);
	cout << "�¼�Ԫʱ��:      " << ctime(&tm2);

	time_t tm3 = system_clock::to_time_t(ppt);
	cout << "�¼�Ԫʱ��+1��:  " << ctime(&tm3);

	time_t tm4 = system_clock::to_time_t(t);
	cout << "�¼�Ԫʱ��+10��: " << ctime(&tm4);

	using namespace std::literals;
	chrono::nanoseconds a = 1ms;
	cout << a.count() <<"  "<< chrono::nanoseconds::period::den <<"  "<< chrono::nanoseconds::period::den / a.count() << endl;

	// ��ȡ��ʼʱ���
	steady_clock::time_point start = steady_clock::now();
	// ִ��ҵ������
	cout << "print 1000 stars ...." << endl;
	for (int i = 0; i < 1000; ++i)
	{
		cout << "*";
	}
	cout << endl;
	// ��ȡ����ʱ���
	steady_clock::time_point last = steady_clock::now();
	// �����ֵ
	auto dt = last - start;
	cout << "�ܹ���ʱ: " << dt.count() << "����" << endl;
}