#include "headers.h"
#include "testlist.hpp"


using func = std::function<void()>;

template<class T>
class C
{

};

template<typename T>
class B
{
public:
	//typedef typename std::vector<T>::iterator Iter;
	using Iter = typename std::vector<T>::iterator;//这种(::)需要明确是类型还是值
	static typename Iter ITER;
};

template<class T>
typename B<T>::Iter B<T>::ITER = std::vector<T>::iterator();


template <typename T> class X
{
	int i;
	std::vector<int> ivec;
	std::vector<int>::iterator iter;

	T type;
	std::vector<T> tvec;
	typename std::vector<T>::iterator titer;
};


class BB
{
	template<class ...Args>
	void pf(Args ...args)
	{

	}
};
  

class F1
{
public:
	 ~F1() {
		cout << " f1" << endl;
	}
};

class F2 : public F1
{
public:
	virtual ~F2()
	{
		cout << "f2" << endl;
	}
};

class Base
{
public:
	virtual void fun(int32 a)
	{
		cout << "int" << endl;
	}

	void fun(double a, int32 b)
	{
	}

	virtual void fun(double a)
	{
		cout << "double" << endl;
	}

};

class SBace : public Base
{
public:
	virtual void fun(int32 a)//会把fun(a,b)覆盖
	{
		cout << "sint" << endl;
	}

	virtual void fun(double a) override
	{
		cout << "sdouble" << endl;
	}
};

#include <variant>

constexpr int getindex(int32 i);

constexpr int getindex(int32 i)
{
	if (i == 0)
	{
		return 1;
	}
}

template<int A>
void tt()
{
	cout << A << endl;
}

class CC
{
public:
	CC() = default;

	~CC()
	{
		cout << "cc" << endl;
	}

	std::map<int32, F2> mp;
	
};

class CCC : public CC
{
public:
	~CCC()
	{
		cout << "ccc" << endl;
	}
};

int main()
{
	std::list<int> li;
	li.size();
	//{
	//	CC *b = new CCC();
	//	b->mp[1];
	//	delete b;
	//}
//#define  BYTESWAP64(A) \
//		(((A&(0xff00'0000'0000'0000))>>56) | (((A&(0x00ff'0000'0000'0000))>>32) | \
//		(((A&(0x0000'ff00'0000'0000))>>16) | ((A&(0x0000'00ff'0000'0000))>>8) | \
//		((A&0x0000'0000'ff00'0000)<<8) | ((A&0x0000'0000'00ff'0000)<<24)) | \
//		((A&0x0000'0000'0000'ff00)<<32) | ((A&0x0000'0000'0000'00ff)<<54))
//	cout << sizeof(float) << "  " << sizeof(double) << endl;
//	auto a = 0xff00'0000;
//	auto b = 0x0000'0000'ff00'0000;
//	cout << a<<" "<< b << endl;

	testTimer();
	//testTimer2();
    system("pause");
    return 0;
}
