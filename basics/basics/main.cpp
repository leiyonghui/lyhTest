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
#include <list>
#include "headers.h"

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

/*
	using arg = std::variant<int, bool>;
	auto tp = std::make_tuple(1, 2);
	std::apply([](auto&& ...args) {
		((cout << args << " "), ...) << endl;
		}, tp);
	auto aa = std::make_from_tuple<AA>(std::move(tp));
	cout << aa.b << "   " << aa.d << endl;
	std::vector<std::tuple<arg, arg, arg, arg>> a;
*/

template<class T>
class object
{
	typedef std::list<T*> List;

	template<class ...Args>
	std::shared_ptr<T> get(Args&& ...args) {
		return std::shared_ptr<T>(new T(std::move(args)...));
	}
};

void print_f(int a)
{
	cout << " a " << a;
}

template<class ...Args>
void print_f(int32 a, Args ...args)
{
	cout << a << " ";
	print_f(args...);
}

int main()
{	
	print_f(1, 2, 3);
	int32 *pt = new int32(1);
	{
		std::shared_ptr<int32> p(pt/*, [](int32 *p) {
			cout << "........" << endl;
		}*/);
		std::make_shared<int32>();
	}
	cout << *pt << endl;
    system("pause");
    return 0;
}