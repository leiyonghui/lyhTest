#include "headers.h"
#include "core/ObjectPools.h"

using namespace std;
using namespace core;


void testPool()
{
	std::shared_ptr<CAObject> aa1;
	std::shared_ptr<Father> F;
	{
		const std::map<int32, int32> bb{ {1,2} };
		auto aa = CObjectPool<CAObject>::Instance()->create(std::move(bb));
		aa->a = 1;
		aa->f = 12;
		//F = ::std::static_pointer_cast<Father>(aa);
		//auto fbb = CObjectPool<A>::Instance()->createUnique();
		//CObjectPoolMonitor::showInfo();
	}
	CObjectPoolMonitor::showInfo();
	//core_log_trace(F->f);
}