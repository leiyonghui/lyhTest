#include "lambda.h"
#include "core/Types.h"
#include <iostream>

using namespace std;
using namespace core;

//���Ƽ�ʹ��'=��Ĭ�ϲ���
TEST(problem1)
{
    static int32 aa = 1;
    auto func = [=]() {  // �޷�����̬ '=' ������Ϊ��ֵ
        cout << "--" << aa << endl;
    };
    func();
    aa = 3;
    func();

    auto fun1 = []() {
        static int32 bb;
        bb++;
        return []() {
            cout <<"bb="<< bb << endl;
        };
    };
    auto fun2 = fun1();
    fun2();
    auto fun3 = fun1();
    fun3();
}

void testLambad()
{
    problem1();
}
