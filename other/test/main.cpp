
#include <iostream>
#include <windows.h>
#include <memory>
#include <string.h>
#include "testlist.hpp"
#include "headers.h"
#include <set>
#include <map>
#include "core/TimeHelp.h"
#include <ctime>
#include <core/Loger.h>
#include <functional>
#include <windows.h>
#include "core/ObjectPools.h"
#include "core/common.h"
#include <list>
#pragma comment(lib, "wsock32.lib")
using namespace std;
using namespace core;

using func = std::function<void()>;

template<class T>
class C
{

};

template<typename T>
class B
{
public:
	//typedef typename std::vector<T>::iterator Iter;
	using Iter = typename std::vector<T>::iterator;//这种(::)需要明确是类型还是值
	static typename Iter ITER;
};

template<class T>
typename B<T>::Iter B<T>::ITER = std::vector<T>::iterator();


template <typename T> class X
{
	int i;
	std::vector<int> ivec;
	std::vector<int>::iterator iter;

	T type;
	std::vector<T> tvec;
	typename std::vector<T>::iterator titer;
};


class BB
{
	template<class ...Args>
	void pf(Args ...args)
	{

	}
};
  

class F1
{
public:
	 ~F1() {
		cout << " f1" << endl;
	}
};

class F2 : public F1
{
public:
	virtual ~F2()
	{
		cout << "f2" << endl;
	}
};

using der = std::function<void(F2*)>;

std::unique_ptr<F2, der> create()
{
	return std::unique_ptr<F2, der>(new F2, [](F2* a) { delete a; });
}

int main()
{
	auto a = CObjectPool<A>::Instance()->create();
	testPool();
	CObjectPool<A>::Instance()->recycle(a);
	CObjectPoolMonitor::showInfo();
    system("pause");
    return 0;
}
