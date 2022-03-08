
#include <iostream>
#include <windows.h>
#include <memory>
#include <string.h>
#include "testlist.hpp"
#include "headers.h"
#include <set>
#include <map>

using namespace std;


class AA {
public:
	AA(int32 a) {

	}
};

int main()
{
    //testChrono();
	//AA a[2];
	//AA b(1);
	//AA* c = new AA[2];
	auto pf = [](string s, const auto& a) {
		cout <<s<<": " << a.size() << "  " << a.capacity() << "  " << (a.empty() ? 0 : a.front()) << endl;
	};
	std::vector<int> a{12, 32};
	//std::vector<int>::iterator a1;
	pf("a", a);
	std::vector<int> b(5, 32);
	b.reserve(3);
	pf("b", b);
	std::vector<int> c;
	c.resize(5);
	pf("c", c);
	cout << c[0] << endl;
	std::vector<int> d;
	d.reserve(5);
	pf("d", d);

	std::vector<std::vector<int>> a1{ {1, 2}, {1, 4} };

	std::set<int> aa;
	d.insert(d.end(), aa.begin(), aa.end());
    system("pause");
    return 0;
}

