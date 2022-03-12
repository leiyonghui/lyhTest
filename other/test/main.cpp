
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
#pragma comment(lib, "wsock32.lib")
using namespace std;
using namespace core;

using func = std::function<void()>;

void F1(func&& f)
{
    func ff(std::move(f));
}

void F2(func&& f) 
{
    F1(std::move(f));
    cout << "222" << endl;
}

int main()
{
	F2([]() {
		cout << "..." << endl;
	});
    core_log_trace(1, "123");
	core_log_error("...");
	core_log_warning("123");
    //testTimer2();
    system("pause");
    return 0;
}

