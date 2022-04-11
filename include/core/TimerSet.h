#include "Configs.h"
#include "Timers.h"

namespace tset
{
	class TimerSet : public IScheduler
	{
	public:
		virtual Tick tick() override { return _curTick; };

		virtual void update(Tick now) override { _update(now); };

		virtual void addTimer(TimerEvent* event) override { _addTimer(event); };

		virtual void delTimer(TimerEvent* event) override { _delTimer(event); };

	protected:
		void _update(Tick now)
		{

		}

		void _addTimer(TimerEvent* event)
		{

		}

		void _delTimer(TimerEvent* event)
		{

		}

	private:
		std::map<int64, TimerSlot*> queue;
		Tick _curTick;
	};
}