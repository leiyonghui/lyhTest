
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

using namespace std;
using namespace core;

int main()
{
    core_log_trace(1, "123");
	core_log_error("...");
	core_log_warning("123");
    system("pause");
    return 0;
}

