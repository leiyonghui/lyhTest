#include "TestInc.h"
#include "Class.h"
#include <iostream>
using namespace std;

void CTestInc::fun(Object1* o)
{
	std::cout << o->_v << endl;
}

CTestFunc::CTestFunc(const std::function<void(const Object1& obj)>& func):_func(func)
{

}
