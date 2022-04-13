#include "core/Configs.h"

namespace permission
{
	using namespace std;

	std::function<void()> func;
	void Bind(std::function<void()> f)
	{
		func = f;
	}

	class object
	{
	public:
		object()
		{
			Bind(std::bind(&object::func, this));//使用bind脱离函数权限
		}


	private:
		virtual void func()
		{
			cout << "ff" << endl;
		}
		friend class Cfriend;
	};

	class object2 : public object
	{
	private:
		virtual void func() override
		{
			cout << "ff2" << endl;
		}
	};

	class Cfriend
	{
	public:
		Cfriend(object* o)//使用虚函数函数权限和友元
		{
			o->func();
		}
	};
}