#include "headers.h"

using namespace std;
using namespace core;

//1.不推荐使用默认捕获
// & 默认按引用捕获可能导致引用悬挂
// 默认按值捕获容易受野指针影响（特别是 this 指针），并且会误导我们，认为 lambda是自给自足的。
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

//2.使用 C++14 的初始化捕获来移动对象至闭包。
// C++11 通过手写类或 std::bind 来模拟初始化捕获。
TEST(problem2)
{
    
}

void test3(int32 a, std::function<void()>)
{

}

TEST(problem3)
{
    int32 id = 0;
    test3(++id, [id]() {//注意顺序
        cout << id << endl;// = 0
    });
}


namespace lambad
{
	void testLambad()
	{
		problem1();
	}
}

