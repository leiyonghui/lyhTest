#include "headers.h"
#include <thread>
#include <chrono>

using namespace std;

//1.��֤std::thread�������������ӽԲ�������
//����������̶߳�����������������ã�����ִ�оͻ���ֹ

//2.std::thread���󲻿ɸ���
TEST(example1)
{
    constexpr auto v = 10'000'000;
    std::thread a([] {
        while(true)
            cout<< 10'000'000 << endl;
     });
    //a.detach();
    cout << ".." << endl;
}


//2:ע���ڴ��ͷţ� ����muduo:examples:asio:timer6 (ps: ���server��loop�ĳ�Ա��û���⣬�첽����ֱ�������þ͵ÿ��ǣ�
namespace example2
{
	class Print {
		string _name;
		//Thread _th;

	public:
		Print(string name) : _name(name)
		{

		}

		~Print()
		{
			cout << "print : destructed!!!" << endl;
		}

		void print1()
		{
			cout << "print1: " << _name << endl;
		}

	};

	class Thread
	{
		std::thread _th;
		Print* _p{ NULL };
	public:

		Thread() : _th(std::thread([this]() {
			while (1)
			{
				if (_p)
					_p->print1();
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			})) {

		}

		void setP(Print* p) { _p = p; }

		~Thread() {
			cout << "--thread destructor" << endl;
			if (_th.joinable())
			{
				cout << " -- join" << endl;
				_th.join();
			}
		}

	};

	TEST(example2)
	{
#ifdef DEBUG
		//�쳣��unique_ptr��ִ��������ɶ��ڴ��ͷţ� thread��ΪʧЧ��ָ��p
		Thread th;
		std::unique_ptr<Print> printPtr;
		printPtr.reset(new Print("name1"));
		th.setP(printPtr.get());
#endif // DEBUG


#ifdef DEBUG
		//��ǰ����������th�Ȼ���ִ��join
		std::unique_ptr<Print> printPtr;
		Thread th;
		printPtr.reset(new Print("name1"));
		th.setP(printPtr.get());
#endif // DEBUG


#ifdef _DEBUG
		if (1)
		{
			//����: ��Ȼpr��ִ���������Ǻ����滻������join��ջ��û�˳��� fix: ���������ط�ռ����ջ�ڴ棿����
			Thread th;
			Print pr("name2");
			th.setP(&pr);
		}
		cout << "............" << endl;
#endif // DEBUG
	}
}

int32 a = 0;
void doadd()
{
	for(int32 i = 1 ;i < 10000; i++)
		++a;
}

namespace add
{
	void testadd()
	{
		//int32 a = 1;
		auto th1 = std::thread(doadd/*[&a] {
			for (int32 i = 1; i < 100000; i++)
			{
				++a;
			}
				
		}*/);
		auto th2 = std::thread(doadd/*[&a] {
			for (int32 i = 1; i < 100000; i++)
			{
				++a;
			}
		}*/);
		th1.join();
		th2.join();
		cout << a << endl;
	}
}
namespace testthread
{
	void testThread()
	{
		add::testadd();
		//example1();
		//example2::example2();
	}
}

