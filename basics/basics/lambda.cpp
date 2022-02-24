#include "lambda.h"
#include "core/Types.h"
#include <iostream>

using namespace std;
using namespace core;

//不推荐使用'=’默认捕获
TEST(problem1)
{
    static int32 aa = 1;
    auto func = [=]() {  // 无法捕获静态 '=' 会误以为传值
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
