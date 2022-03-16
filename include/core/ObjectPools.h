#pragma once
#include "Types.h"
#include "Singleton.h"
#include <list>
#include <memory>
#include <map>
#include <string.h>
#include <functional>


class CObjectPoolMonitor
{
	static std::map<std::string, std::function<void()>> ObjectPoolMap;
public:
	static void monitorPool(std::string name, std::function<void()>&& func)
	{
		ObjectPoolMap[name] = std::move(func);
	}

	static void delMonitorPool(const std::string& name)//?
	{
		ObjectPoolMap.erase(name);
	}

	static void showInfo()
	{
		for (const auto&[name, func] : ObjectPoolMap)
			func();
	}
};
std::map<std::string, std::function<void()>> CObjectPoolMonitor::ObjectPoolMap;


#define INIT_OBJECT_SIZE 16
template<class T>
class CObjectPool : public CSingleton<CObjectPool<T>>
{
	using List = std::list<T*>;

public:
	CObjectPool():_useCount(0),_freeCount(0) {
		CObjectPoolMonitor::monitorPool(typeid(T).name(), [this]() { this->printInfo(); });
	}

	virtual~CObjectPool() {
		auto iter = _list.begin();
		while (iter != _list.end())
		{
			delete *iter;
			_list.erase(iter++);
		}
	}
	
	template<class ...Args>
	std::shared_ptr<T> create(Args ...args)
	{
		while (_list.empty())
			assignObjs(INIT_OBJECT_SIZE);
		T* ptr = _list.front();
		_list.pop_front();
		ptr->onAwake(std::forward<Args>(args)...);
		++_useCount;
		--_freeCount;
		return std::shared_ptr<T>(ptr, [this](T* ptr) { this->recycle(ptr); });
	}

	void printInfo()
	{
		cout << typeid(T).name() <<" use:"<< _useCount << " free:" << _freeCount<< endl;
	}

private:
	List _list;
	int32 _useCount;
	int32 _freeCount;

	void recycle(T* ptr) {
		if (ptr) {
			ptr->onRecycle();
			_list.push_back(ptr);
			++_freeCount;
			--_useCount;
		}
	}

	void assignObjs(int32 amount) {
		for (int32 i = 0; i < amount; ++i, ++_freeCount)
			_list.push_back(new T());
	}
};

