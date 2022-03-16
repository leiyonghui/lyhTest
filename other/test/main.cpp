
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

	template<class ...Args>
	void pf(Args ...args)
	{

	}
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

