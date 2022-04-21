#pragma once
#include "headers.h"

class A
{
public:
	A() = default ;

	A(const A& a) {
		cout << " left copy " << endl;
	}

	A(A&& a) {
		cout << " right copy" << endl;
	}
};

namespace t1
{
	//带有&或者*的形参，将实参忽略&或者*进行匹配
	template<class T>
	void fun1(T& p){}

	template<class T>
	void fun2(const T& p){}

	void t()
	{
		int32 a;
		int32& b = a;
		const int32 c = 1;
		const int32& d = c;
		fun1(a);//<int>(int&)
		fun1(b);//<int>(int&)
		fun1(c);//<const int>(const int&)
		fun1(d);//<const int>(const int&)
		fun2(a);//<int>(const int&)
		fun2(b);//<int>(const int&)
		fun2(c);//<int>(const int&)
		fun2(d);//<int>(const int&)
		fun2(12);//<int>(const int&)
	}
}

namespace t2
{
	//右值引用

	/*
		非引用返回的临时变量，运算表达式产生的临时变量，原始字面变量和lambda表达式都是纯右值
		无论左值引用还是右值引用都必须立即初始化，因为引用并不拥有所绑定变量的内存，通过右值引用的声明可以实临时变量重新复活
	*/
	template<class T>
	void fun1(T&& p){}//T&&未定引用（只有自动发生类型推导判断时），按传左值:按&进行匹配, 右值: 常规匹配

	template<class T>
	void fun2(const T&& p){}//被const修饰普通右值

	int32 geta() { return 12; }

	void fun3(A&& a)
	{
		A b = a;//left copy
		A c = std::move(a);//right copy
	}

	void fun4(A&)
	{

	}

	void fun5(const A&)
	{

	}

	A getA() {
		return A();
	}

	void t()
	{
		int32 a = 1;
		int32& b = a;
		const int32 c = 12;
		const int32& d = a;
		int32&& e = geta();//左值，右值引用，
		const int32& f = 12;//const xx& 万能引用 //左值，右值引用
		const int32&& g = 12;//左值，右值引用
		fun1(a);//<int&>(int&)
		fun1(b);//<int&><int&>
		fun1(c);//<const int&>(const int&)
		fun1(d);//<const int&>(const int&)
		fun1(e);//<int&>(int&)
		fun1(f);//<const int&>(const int&)
		fun1(g);//<const int&>(const int&)
		fun1(12);//<int>(int&&)

		//fun2(a);error
		//fun2(b);error
		//fun2(c);error
		//fun2(d);error
		//fun2(e);error
		//fun2(f);error
		//fun2(g);error
		fun2(12);//<int>(const int&&)

		A a2;
		//fun3(aa);

		//fun3(A());
		//fun4(A());error
		////fun5(A());

		A a3 = std::move(a2);//right copy

		A&& a4 = getA();
		A a5 = a4;//left copy
		A a6 = getA();
	}
}

namespace t3
{
	template<class T>
	void fun1(T p){}//传值，去掉const,volatile,修饰

	void t()
	{
		int32 a;
		const int32 b = 1;
		int32& c = a;
		const int32& d = a;
		volatile int e = 0;
		fun1(a);//<int>(int)
		fun1(b);//<int>(int)
		fun1(c);//<int>(int)
		fun1(d);//<int>(int)
		fun1(12);//<int>(int)
		fun1(e);//<int>(int)
	}
}

namespace t4
{
	//auto 和模板推导一样 
	//但是auto会假定使用大括号的是一个std::initilalizer_list但是模板不会
	//函数返回值使用auto或者lambda形参使用auto是使用模板型别推导而非auto

	/*错误 auto fun1()
	{
		return {1, 2};
	}*/

	template<class T, class B>
	void ff(const T& t1, const B& b2)
	{
		core_log_error("---", &t1, &b2);
	}

	template<class T>
	void ft(T&& t)
	{
		core_log_debug("..", & t);
		T b = t;
	}

	void t()
	{
		auto f = [](const int& p1, const int& p2) {
			core_log_error(&p1, &p2);
		};
		//int32 a = 1;
		//f(12, a);
		//ff(12, a);
		core_log_debug(&f);
		ft([](const int& p1, const int& p2) {
			core_log_error(&p1, &p2);
			});
	}
}