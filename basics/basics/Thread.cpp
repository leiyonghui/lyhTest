#include "Thread.h"
#include <thread>
#include <iostream>

using namespace std;

TEST(example1)
{
    constexpr auto v = 10'000'000;
    std::thread a([] {
        cout<< " === " << endl;
     });
    a.detach();
    cout << ".." << endl;
}

void testThread()
{
    example1();
}
