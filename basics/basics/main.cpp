#include <atomic>                                                                
#include <stdio.h>
#include <iostream>
#include <chrono>
#include "constructor.h"
#include "lambda.h"
#include "Thread.h"
#include <memory>
#include "core/Types.h"

using namespace core;
//using namespace std;
//using namespace std::chrono;
//using namespace std::literals;


int main()
{
    testThread();
    system("pause");
    return 0;
}