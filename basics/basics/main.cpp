#include <atomic>                                                                
#include <stdio.h>
#include <iostream>
#include <chrono>
#include "constructor.h"
#include "lambda.h"
#include "Thread.h"
#include <memory>
#include "core/Types.h"
#include "destructor.h"
#include "StdPtr.h"

using namespace core;
//using namespace std;
//using namespace std::chrono;
//using namespace std::literals;


int main()
{
	//testDestructor();
	//testThread();
	testShare();
    system("pause");
    return 0;
}