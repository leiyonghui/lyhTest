#pragma once
#include <functional>

class Object1;

class CTestInc
{
public:
	void fun(Object1* o);
};


class CTestFunc
{
public:
	CTestFunc(const std::function<void(const Object1& obj)>& func);

	std::function<void(const Object1& obj)> _func;
};