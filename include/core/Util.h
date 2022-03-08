#pragma once
namespace util
{
	template<typename T>
	struct CEmpty
	{
		static const T Empty;
	};

	template<typename T>
	const T CEmpty<T>::Empty = T();


}