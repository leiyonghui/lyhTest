#include "headers.h"
#include "core/ObjectPools.h"

using namespace std;
using namespace core;


void testPool()
{
	std::shared_ptr<A> aa1;
	std::shared_ptr<Father> F;
	{
		auto aa = CObjectPool<A>::Instance()->create();
		aa->a = 1;
		aa->f = 12;
		F = ::std::static_pointer_cast<Father>(aa);
		auto fbb = CObjectPool<A>::Instance()->createUnique();
		CObjectPoolMonitor::showInfo();
	}
	CObjectPoolMonitor::showInfo();
	core_log_trace(F->f);
}