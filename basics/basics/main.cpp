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
    //testThread();
    char* c = new char;
    auto b = c + 1;
    void* d = new char;
    //auto e = d + 1;
    cout << c + 1 << "   "<< sizeof(void*) << endl;;
    system("pause");
    return 0;
}