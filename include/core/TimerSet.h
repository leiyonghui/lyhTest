#include "Configs.h"
#include "Timers.h"

namespace tset
{
	class Set
	{
		std::map<int64, TimerSlot*> queue;
	};
}