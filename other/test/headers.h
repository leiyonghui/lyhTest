#pragma once
#include <iostream>
#include "core/ObjectPools.h"
#include "core/Configs.h"

#define TEST(NAME) void test_##NAME()

void testbuff();

void testChrono();

void testTimer();

void testTimer2();

void testPool();

class Father {
public:
	Father() = default;
	int f;
};

class A : public core::CPoolObject, public Father
{
public:
	int a;

	void onAwake() {
		std::cout << "--awake" << std::endl;
	}

	void onRecycle()
	{
		std::cout << "--recycle" << std::endl;
	}

	template<class ...Args>
	void pf(Args ...args)
	{

	}
};