#include "Thread.h"
#include <thread>
#include <iostream>

using namespace std;

//1.保证std::thread对象在所有连接皆不可联结
//如果可联结线程对象的析构函数被调用，程序执行就会终止

//2.std::thread对象不可复制
TEST(example1)
{
    std::thread a([] {
        while(true)
            cout<< 10'000'000 << endl;
     });
    //a.detach();
    cout << ".." << endl;
}

void testThread()
{
    example1();
}
