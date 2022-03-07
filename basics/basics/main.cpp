#include <atomic>                                                                
#include <stdio.h>
#include <vector>
#include <iostream>
#include <chrono>
#include "constructor.h"
#include "lambda.h"
#include "Thread.h"
#include <memory>
#include "core/Types.h"
#include "destructor.h"
#include "StdPtr.h"
#include <tuple>
#include <variant>
#include <iostream>

using namespace core;
using namespace std;
//using namespace std;
//using namespace std::chrono;
//using namespace std::literals;

class AA {

public:
	AA(int bb, bool dd):b(bb), d(dd) {

	}

	int b;
	bool d;
};


int main()
{
	//testDestructor();
	//testThread();
	//testShare();
	//cout << 'f' << 'n' << 'r';
	using arg = std::variant<int, bool>;

	auto tp = std::make_tuple(1, 2);
	std::apply([](auto&& ...args) {
		((cout << args << " "), ...) << endl;
		}, tp);
	auto aa = std::make_from_tuple<AA>(std::move(tp));
	cout << aa.b << "   " << aa.d << endl;

	std::vector<std::tuple<arg, arg, arg, arg>> a;
    system("pause");
    return 0;
}