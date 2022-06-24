#pragma once
#include "core/Configs.h"
#include "core/ObjectPools.h"
#include "core/Common.h"
#include "core/KeyPool.h"
#include <windows.h>

#pragma comment(lib, "wsock32.lib")

#define TEST(NAME) void test_##NAME()

using namespace std;
using namespace core;

struct CStartup
{
	using Func = std::function<void()>;
	static std::map<std::string, Func>& GetList()
	{
		static std::map<std::string, Func> list;
		return list;
	}

	static void Register(const std::string& name, const Func& func)
	{
		auto& list = GetList();
		core::insert(list, name, func);
	}

	CStartup(const std::string& name, const Func& func)
	{
		Register(name, func);
	}
};

#define MAKE_CODE_REGISTER(FuncName) static CStartup  __startup(#FuncName, FuncName)