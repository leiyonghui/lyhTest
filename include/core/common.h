#pragma once
#include "Configs.h"

namespace core
{
	template< typename U, typename K, typename V>
	const U find(const std::map<K, V>& container, const K& key, const U& vaule)
	{
		auto iter = container.find(key);
		if (iter == container.end())
		{
			return vaule;
		}
		return iter->second;
	}
}