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
			Bind(std::bind(&object::func, this));//ʹ��bind���뺯��Ȩ��
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
		Cfriend(object* o)//ʹ���麯������Ȩ�޺���Ԫ
		{
			o->func();
		}
	};
}