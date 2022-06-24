#include "TestClass.h"
#include "TestInc.h"
#include <iostream>
using namespace std;

void CTestInc::fun(Object1* o)
{
	std::cout << o->_v << endl;
}