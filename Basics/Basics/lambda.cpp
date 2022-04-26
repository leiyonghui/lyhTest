#include "headers.h"

using namespace std;
using namespace core;

//1.���Ƽ�ʹ��Ĭ�ϲ���
// & Ĭ�ϰ����ò�����ܵ�����������
// Ĭ�ϰ�ֵ����������Ұָ��Ӱ�죨�ر��� this ָ�룩�����һ������ǣ���Ϊ lambda���Ը�����ġ�
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

//2.ʹ�� C++14 �ĳ�ʼ���������ƶ��������հ���
// C++11 ͨ����д��� std::bind ��ģ���ʼ������
TEST(problem2)
{
    
}

void test3(int32 a, std::function<void()>)
{

}

TEST(problem3)
{
    int32 id = 0;
    test3(++id, [id]() {//ע��˳��
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

