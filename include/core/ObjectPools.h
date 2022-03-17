#pragma once
#include "Types.h"
#include "Singleton.h"
#include <list>
#include <memory>

#define INIT_OBJECT_SIZE 16

template<class T>
class CObjectPool : public CSingleton<CObjectPool<T>>
{
	using List = std::list<T*>;

	//using Iterator = std::list<T*>::const_iterator;
public:
	//const static Iterator NullIter;

	CObjectPool():_useCount(0),_freeCount(0) {}

	virtual~CObjectPool() {
		auto iter = _freeObjects.begin();
		while (iter != _freeObjects.end())
		{
			delete *iter;
			_freeObjects.erase(iter++);
		}
	}
	
	template<class ...Args>std::shared_ptr<T> create(Args ...args)
	{
		while (_freeObjects.empty())
			assignObjs(INIT_OBJECT_SIZE);
		T* ptr = _freeObjects.front();
		_freeObjects.pop_front();
		ptr->setOjectorIter(_usingOjects.end(), _usingOjects.insert(ptr));
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
	List _freeObjects;
	List _usingOjects;
	int32 _useCount;
	int32 _freeCount;

	void recycle(T* ptr) {
		auto iter = ptr->getObjectorIter();
		if (ptr) {
			ptr->onRecycle();
			_usingOjects.erase(iter);
			ptr->setOjectorIter(_usingOjects.end());
			_freeObjects.push_back(ptr);
			++_freeCount;
			--_useCount;
		}
	}

	void assignObjs(int32 amount) {
		for (int32 i = 0; i < amount; ++i, ++_freeCount)
			_freeObjects.push_back(new T());
	}
};

//template<typename T>
//const CObjectPool<T>::Iterator CObjectPool<T>::NullIter = std::list<T*>::iterator();