#include "destructor.h"
#include "core/Types.h"
#include <iostream>

using namespace std;

class Destructor
{
public:
	string name;

	Destructor(string n):name(n){}

	~Destructor() {
		cout <<" destructing!!! " << name<< endl;
	}
};

class Destructor2 {
public:
	~Destructor2() {
		cout << "Destructor2" << endl;
	}
};

//²âÊÔÊÍ·ÅË³Ðò c b d2 a
void func1(Destructor a)
{
	Destructor2 d2;
	Destructor b("b");
	Destructor c("c");
}

void testDestructor()
{
	func1(Destructor("p"));
}
