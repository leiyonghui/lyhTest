#pragma once
#include "configs.h"

void testbuff();

void testChrono();

void testTimer();

void testTimer2();
void testTimer3();

void testTimer3();

void testPool();

void testShare();

class Father {
public:
	Father() {
		core_log_debug("test1");
	}
	int f;
};

class CAObject : public core::CPoolObject, public Father
{
public:
	int a;
	std::map<int, int> mp;
	std::unique_ptr<int32> ptr;

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

	void onAwake(std::unique_ptr<int32> p)
	{
		core_log_debug("======uni");
		ptr = std::move(p);
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