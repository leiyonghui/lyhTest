#include "Thread.h"
#include <thread>
#include <iostream>

using namespace std;

//1.��֤std::thread�������������ӽԲ�������
//����������̶߳�����������������ã�����ִ�оͻ���ֹ

//2.std::thread���󲻿ɸ���
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
