#include "headers.h"
#include "testlist.hpp"
#include "core/IntrusiveNode.h"
#include "core/Macro.h"
#include "RingBuffer.h"

//int* ptr[2];
//int(*)ptr[2];
//int* ptr();
//int(*)ptr();
//int(*((*ptr(int, int))))(int);

//Obj* ptr = static_cast<Obj*>(::operator new(sizeof(Obj)));
//auto a = new(ptr)Obj(2);
//cout << ptr->value << "   " << a->value << endl;
//cout << &ptr->value << "   " << &a->value << endl;

class Obj;

class Obj
{
public:
	Obj(int32 v) :value(v)
	{

	}

	virtual ~Obj()
	{
		cout << " del" << endl;
	}

	int32 value;
};

class Obj;


#include "Class.h"
#include "TestInc.h"

int main(int argc, char** argv)
{
	Obj* ptr = new Obj(12);
	cout << sizeof(Obj) <<"  "<<sizeof(int64)<< endl;
	auto obj = Object1(12);

	CTestFunc fun([](const Object1& obj) {
		
	});

	cout << sizeof(std::function<void(const Object1& obj)>) << endl;

	cout << sizeof(std::function<Object1(int32 a, int32 b)>) << endl;

	cout << sizeof(std::function<int64(int32 a, int32 b, int32 c, int64 d)>) << endl;

	std::function<int64(int32, int32, int32)> f = [](int, int, int) { return 0; };
    return 0;
}



