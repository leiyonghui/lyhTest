#pragma once
#include <iostream>
#include "core/ObjectPools.h"
#include "core/Configs.h"

#define TEST(NAME) void test_##NAME()

void testbuff();

void testbuff();

void testChrono();

void testTimer();

void testTimer2();

void testPool();

void testShare();

class Father {
public:
	Father() = default;
	int f;
};

class A : public core::CPoolObject, public Father
{
public:
	int a;
	std::map<int, int> mp;

	void onAwake(const std::map<int, int>& m) {
		std::cout << "1--awake1 " << m.size() << std::endl;
		mp = m;
		std::cout << "1--awake2 " << m.size() << "  " << mp.size() << std::endl;
	}

	void onAwake(std::map<int, int>&& m) {
		std::cout << "--awake1 "<< m.size() << std::endl;
		mp = std::move(m);
		std::cout << "--awake2 " << m.size() <<"  "<< mp.size() << std::endl;
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