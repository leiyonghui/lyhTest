////#include "headers.h"
////#include "testlist.hpp"
////#include "core/IntrusiveNode.h"
////#include "core/Macro.h"
////#include "RingBuffer.h"
//#include <list>
//#include <algorithm>
//
////int* ptr[2];
////int(*)ptr[2];
////int* ptr();
////int(*)ptr();
////int(*((*ptr(int, int))))(int);
//
////Obj* ptr = static_cast<Obj*>(::operator new(sizeof(Obj)));
////auto a = new(ptr)Obj(2);
////cout << ptr->value << "   " << a->value << endl;
////cout << &ptr->value << "   " << &a->value << endl;
//
////class Object : public std::enable_shared_from_this<Object>
////{
////public:
////	Object()
////	{
////
////	}
////
////	~Object()
////	{
////		auto w = weak_from_this();
////		cout << w.expired() << endl;
////		auto p = shared_from_this();
////		cout << p->v << endl;
////	}
////
////	int32 v{ 3 };
////};
//
//
//// case1: T* can cast to C*
////template <template <typename...> class C, typename...Ts>
////std::true_type is_base_of_template_impl(const C<Ts...>*);
////// case2: T* cannot cast to C*
////template <template <typename...> class C>
////std::false_type is_base_of_template_impl(...);
////
////template <template <typename...> class C, typename T>
////using is_base_of_template = decltype(is_base_of_template_impl<C>(std::declval<T*>()));
//
////template<class T>
////class Base
////{
////
////};
////
////class ClassA : public Base<ClassA>
////{
////
////};
////
////class ClassB : public std::enable_shared_from_this<ClassB>
////{
////
////};
////
////template<class T, std::enable_if_t<is_base_of_template<std::enable_shared_from_this, T>::value, int> = 0>
////class Object
////{
////	static_assert(is_base_of_template<std::enable_shared_from_this, T>::value);
////};
//
//
//template <template <typename...> class BaseTemplate, typename Derived, typename TCheck = void>
//struct test_base_template;
//
//template <template <typename...> class BaseTemplate, typename Derived>
//using is_base_of_template = typename test_base_template<BaseTemplate, Derived>::is_base;
//
////Derive - is a class. Let inherit from Derive, so it can cast to its protected parents
//template <template <typename...> class BaseTemplate, typename Derived>
//struct test_base_template<BaseTemplate, Derived, std::enable_if_t<std::is_class_v<Derived>>> : Derived {
//	template <typename... T>
//	static constexpr std::true_type test(BaseTemplate<T...>*);
//	static constexpr std::false_type test(...);
//	using is_base = decltype(test((Derived*)nullptr));
//};
//
////Derive - is not a class, so it is always false_type
//template <template <typename...> class BaseTemplate, typename Derived>
//struct test_base_template<BaseTemplate, Derived, std::enable_if_t<!std::is_class_v<Derived>>> {
//	using is_base = std::false_type;
//};
//
//struct Block
//{
//	Block(int32 a = 0):a(a)
//	{
//		cout << "---bb" << endl;
//	}
//
//	~Block()//如果不delect不会执行
//	{
//		cout << "---d" << endl;
//	}
//
//	int32 a;
//};
//
//struct Block2 
//{
//	Block b;
//
//	template<class T>
//	void TC(int32 a)
//	{
//		cout << a << endl;
//	}
//};
//
////template<class T>
////struct TC
////{
////	template<class ...Args>
////	T f(Args ...arg)
////	{
////		//cout << arg << endl;
////	}
////};
//
//
//template<class T, class F>
//void tF(T v, F f)
//{
//
//}
//
//template<>
//void tF<>(char, const char*)
//{
//
//}
//
//int main(int argc, char** argv)
//{
//	//TC<Block> b;
//	//b.f<Block>(12);
//
//	//Logger::Instance(new Logger(new ConsoleLogAppender()));
//
//	////testPool();
//
//	//{
//	//	std::vector<Block> a;
//	//	a.emplace_back(2);
//	//	cout << "---------1 " << a.capacity() << endl;
//	//	a.emplace_back(2);
//	//	cout << "---------2 " << a.capacity() << endl;
//	//	a.emplace_back(2);
//	//	cout << "---------3 " << a.capacity() << endl;
//	//	a.emplace_back(2);
//	//	cout << "---------4 " << a.capacity() << endl;
//	//	a.emplace_back(2);
//	//	cout << "---------5 " << a.capacity() << endl;
//	//}
//	//tF<int, int>();
//	//Logger::Instance()->stop();
//	std::list<int> ls;
//	ls.insert(1);
//	auto iter = ls.begin();
//	auto it = std::next(ls.begin() + 3);
//	if (it == ls.end())
//	{
//		cout << "---------1" << endl;
//	}
//
//    return 0;
//}
//
//
//
#include <iostream> 
#include <iterator> 
#include <deque> 
#include <algorithm> 
#include <list>
using namespace std;

#include"Activity.h"

int main()
{
	Activity act;
	act.init();
	return 0;
}