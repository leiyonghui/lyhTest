#include "headers.h"
#include "core/ObjectPools.h"

using namespace std;
using namespace core;

class Object2
{
public:
	Object2(int32 v):a(v)
	{
		core_log_info("object2");
	}

	Object2(std::vector<int32> a)
	{
		core_log_info("object2 222");

	}

	virtual ~Object2()
	{
		core_log_info("del object2");

	}

	int32 a;
};

void testPool()
{
	std::shared_ptr<CAObject> aa1;
	std::shared_ptr<Father> F;
	{
		std::map<int32, int32> bb{ {1,2} };
		auto aa = CObjectPool<CAObject>::Instance()->create(12);
		aa->a = 1;
		aa->f = 12;
	}
	CObjectPoolMonitor::showInfo();

	//auto ptr = ::operator new(sizeof(Object2));

	//new(ptr) Object2(12);

	{
		int32 v = 12;
		auto obj = CObjectPool<Object2>::Instance()->create<Object2>(12);

		//cout <<"a = "<< obj->a << endl;
		CObjectPoolMonitor::showInfo();
		//obj = nullptr;
	}
	CObjectPoolMonitor::showInfo();
}

void func1()
{
	std::cout << "----p" << endl;
}

MAKE_CODE_REGISTER(func1);
//CStartup("1", func1);