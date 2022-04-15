#pragma once
#include "core/Configs.h"
#include "core/ObjectPools.h"
#include "core/Configs.h"
#include <windows.h>

#pragma comment(lib, "wsock32.lib")

#define TEST(NAME) void test_##NAME()

using namespace std;
using namespace core;