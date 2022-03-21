
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


class Father {
public:
	Father() = default;
	int32 f;
};

class A : public CPoolObject<A>, public Father
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
	virtual ~F1() {
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

int main()
{
	std::vector<int32> a;
	a.push_back(1);
	a.push_back(1);
	a.push_back(1);
	auto iter = a.end() - 1;
	cout << a.end()  - a.begin() << endl;
    system("pause");
    return 0;
}

/*
CObjectPool<A>::Instance(new CObjectPool<A>);
	std::shared_ptr<A> aa1;
	std::shared_ptr<Father> F;
	{
		auto aa = CObjectPool<A>::Instance()->create();
		aa->a = 1;
		aa->f = 12;
		//aa1 = aa;
		F = ::std::static_pointer_cast<Father>(aa);
		CObjectPoolMonitor::showInfo();
	}
	//CObjectPool<A>::Instance()->printInfo();
	CObjectPoolMonitor::showInfo();
	cout << F->f << endl;


	std::map<int32, int32> mapa;
	mapa[1] = 1;
	const int32 k = 1;
	cout << core::find(mapa, 1, 0) << endl;*/