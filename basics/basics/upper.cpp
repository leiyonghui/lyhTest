#include "headers.h"

using namespace std;

void testUpper()
{
	int32 len = 10;
	std::vector<int32> vec;
	for (int32 i = 1; i <= len; i++)
	{
		vec.push_back(i);
	}
	auto iter = std::lower_bound(vec.begin(), vec.end(), 1, [](int32 a, int32 b) -> bool {
		return a < 5;
	});
	if (iter != vec.end()) 
	{
		cout << *iter << endl;
	}
	else
	{
		cout << "..." << endl;
	}
}