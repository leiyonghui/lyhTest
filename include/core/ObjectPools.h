#pragma once
#include "Configs.h"

namespace core
{
	class CObjectPoolMonitor
	{
		using ObjectMap = std::map<std::string, std::function<void()>>;
	public:
		static ObjectMap& getObjectPool()
		{
			static ObjectMap ObjectPoolMap;//以免Monitor还未创建
			return ObjectPoolMap;
		}

		static void monitorPool(std::string name, std::function<void()>&& func)
		{
			auto& objectPoolMap = getObjectPool();
			assert(objectPoolMap.find(name) == objectPoolMap.end());
			objectPoolMap[name] = std::move(func);
		}

		static void showInfo()
		{
			auto& objectPoolMap = getObjectPool();
			core_log_info("ObjectPoolInfo start:", TimeHelp::TimeToString(TimeHelp::now()));
			for (const auto& iter : objectPoolMap)
				iter.second();
			core_log_info("ObjectPoolInfo end.");
		}
	};


#define INIT_OBJECT_SIZE 16
	template<class T>
	class CObjectPool
	{
		using List = std::list<T*>;
		using Iterator = typename std::list<T*>::iterator;
		using Deleter = typename std::function<void(T*)>;
	public:
		const static Iterator NullIter;

		CObjectPool(int32 size = INIT_OBJECT_SIZE) :_useCount(0), _freeCount(0), _assignSize(size){
			CObjectPoolMonitor::monitorPool(typeid(T).name(), [this]() { this->printInfo(); });
		}

		virtual~CObjectPool() {

		}

		static CObjectPool<T>* Instance()
		{
			if (_instance == nullptr)
				_instance = new CObjectPool<T>();
			return _instance;
		}

		static CObjectPool<T>* Instance(CObjectPool<T>* o)
		{
			assert(_instance == nullptr);
			_instance = o;
			return _instance;
		}
		
		template<class ...Args>
		T* create(const Args& ...args)
		{
			auto ptr = popObject();
			ptr->onAwake(args...);
			return ptr;
		}

		template<class ...Args>
		T* create(Args&& ...args)
		{
			auto ptr = popObject();
			ptr->onAwake(std::forward<Args>(args)...);
			return ptr;
		}

		template<class ...Args>
		std::shared_ptr<T> createShare(const Args& ...args)
		{
			auto ptr = popObject();
			ptr->onAwake(args...);
			return std::shared_ptr<T>(ptr, [this](T* ptr) { this->recycle(ptr); });
		}

		template<class ...Args>
		std::shared_ptr<T> createShare(Args&& ...args)
		{
			core_log_info("createShare");
			auto ptr = popObject();
			ptr->onAwake(std::forward<Args>(args)...);
			return std::shared_ptr<T>(ptr, [this](T* ptr) { this->recycle(ptr); });
		}

		template<class ...Args>
		std::unique_ptr<T, Deleter> createUnique(const Args& ...args)
		{
			auto ptr = popObject();
			ptr->onAwake(args...);
			return std::unique_ptr<T, Deleter>(ptr, [this](T* ptr) { this->recycle(ptr); });
		}

		template<class ...Args>
		std::unique_ptr<T, Deleter> createUnique(Args&& ...args)
		{
			auto ptr = popObject();
			ptr->onAwake(std::forward<Args>(args)...);
			return std::unique_ptr<T, Deleter>(ptr, [this](T* ptr) { this->recycle(ptr); });
		}

		void recycle(T* ptr) {
			if (ptr && ptr->isUsing()) {
				ptr->onRecycle();
				ptr->setUsing(false);
				_freeObjects.push_back(ptr);
				++_freeCount;
				--_useCount;
			}
		}

		void printInfo()
		{
			core_log_info(typeid(T).name(), "using:", _useCount, "free:", _freeCount);
		}

	private:
		static CObjectPool<T>* _instance;

		List _freeObjects;
		int32 _useCount;
		int32 _freeCount;
		int32 _assignSize;

		T* popObject()
		{
			while (_freeObjects.empty())
				assignObjs(_assignSize);
			T* ptr = _freeObjects.front();
			_freeObjects.pop_front();
			ptr->setUsing(true);
			++_useCount;
			--_freeCount;
			return ptr;
		}

		void assignObjs(int32 amount) {
			for (int32 i = 0; i < amount; ++i, ++_freeCount)
				_freeObjects.push_back(new T());
		}
	};

	template<class T>
	const typename CObjectPool<T>::Iterator CObjectPool<T>::NullIter = CObjectPool<T>::Iterator();

	template<class T>
	CObjectPool<T>* CObjectPool<T>::_instance = nullptr;

	class CPoolObject
	{
	public:
		CPoolObject() :_using(false) {}

		void setUsing(bool use) { _using = use; };

		bool isUsing() const { return _using; }
	protected:
		bool _using;
	};

}