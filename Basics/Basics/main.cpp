#include <atomic>                                                                
#include <stdio.h>
#include "headers.h"
#include "template.h"
#include "类型推导.h"
#include "object.h"

struct PlayerTag
{
	using type = int;
};

PlayerTag player;

struct RoleTag
{
	using type = int;
};

RoleTag role;

class AB
{
public:
	template<class T>
	typename T::type operator[](T)
	{
		thread_local static T::type a;
		a++;
		cout << "---"<< a;
		return T::type();
	}
};

class AAB
{
public:

};

//struct T {
//	enum { int_t, float_t } m_type;
//	template <typename Integer,
//		typename B = std::enable_if_t<std::is_integral_v<Integer>>
//	>
//		T(Integer) : m_type(int_t) {}
//
//	template <typename Floating,
//		typename B = std::enable_if_t<std::is_floating_point_v<Floating>>
//	>
//		T(Floating) : m_type(float_t) {} // 错误：不能重载
//};

struct T {
	enum { int_t, float_t } m_type;
	template <typename Integer,
		std::enable_if_t<std::is_integral_v<Integer>> = 0
	>
		T(Integer) : m_type(int_t) {}

	template <typename Floating,
		std::enable_if_t<std::is_floating_point_v<Floating>> = 0
	>
		T(Floating) : m_type(float_t) {} // OK
};

struct Type
{
	using type = int;
};

struct Type2
{
	using type = long;
};

template<class T, typename T::type = 0>
void t_type(T)
{

}


template<class T>
void destroy(
	T*,
	typename std::enable_if<
	std::is_trivially_destructible<T>::value
	>::type* = 0
) {
	std::cout << "destroying trivially destructible T\n";
}

template<uint32 size, std::enable_if_t<size < 32, int> = 0>
class TArray
{
public:
	TArray() = default;
};

int main()
{
	testthread::testThread();
    system("pause");
    return 0;
}