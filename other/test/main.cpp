
#include <iostream>
#include <windows.h>
#include <memory>
#include <string.h>
#include "testlist.hpp"
#include "testtimer.hpp"
#include "headers.h"

using namespace std;


int main()
{
	std::shared_ptr<int32> ptr = std::make_shared<int32>(int32(0));
    system("pause");
    return 0;
}

