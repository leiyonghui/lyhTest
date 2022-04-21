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
	template<class T>
	void fun1(T&& p){}//T&&不确定引用，按传左值为&, 右值则匹配

	template<class T>
	void fun2(const T&& p){}//const修饰，必须右值

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
		fun1(a);
		fun1(b);
		fun1(c);
		fun1(d);
		fun1(e);
		fun1(f);
		fun1(g);

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