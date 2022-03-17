
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
#include <list>
#pragma comment(lib, "wsock32.lib")
using namespace std;
using namespace core;

using func = std::function<void()>;


class A
{
public:
    int32 a;

    void onAwake() {
        cout << "--awake" << endl;
    }

    void onRecycle()
    {
		cout << "--recycle" << endl;
    }

	void setOjectorIter(std::list<A*>::iterator iter)
	{

	}

	std::list<A*>::iterator getObjectorIter()
	{
		return std::list<A*>::iterator();
	}

	template<class ...Args>
	void pf(Args ...args)
	{

	}
};


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


int main()
{
    CObjectPool<A>::Instance(new CObjectPool<A>);
    {
		auto aa = CObjectPool<A>::Instance()->create();
		aa->a = 1;
    }
    //CObjectPool<A>::Instance()->printInfo();
    CObjectPoolMonitor::showInfo();
    system("pause");
    return 0;
}

