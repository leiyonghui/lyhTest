
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

class A : public CPoolObject, public Father
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

class Base
{
public:
	virtual void fun(int32 a)
	{
		cout << "int" << endl;
	}

	void fun(double a, int32 b)
	{
	}

	virtual void fun(double a)
	{
		cout << "double" << endl;
	}

};

class SBace : public Base
{
public:
	virtual void fun(int32 a)//会把fun(a,b)覆盖
	{
		cout << "sint" << endl;
	}

	virtual void fun(double a) override
	{
		cout << "sdouble" << endl;
	}
};

#include <variant>

constexpr int getindex(int32 i);

constexpr int getindex(int32 i)
{
	if (i == 0)
	{
		return 1;
	}
}

template<int A>
void tt()
{
	cout << A << endl;
}

int main()
{
	testShare();
    system("pause");
    return 0;
}
