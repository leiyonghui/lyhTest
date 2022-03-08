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


	template<class T>
	class CSwitch
	{
		using Values = std::vector<T>;

		std::vector<Values> _t;
		short _index;

	public:
		CSwitch() : _index(0) {
			_t.resize(2);
			_t[0].reserve(8);
			_t[1].reserve(8);
		}

		CSwitch(const Values& t1, const Values& t2) : _t{ t1, t2 }, _index(0) {

		}

		Values& first() { return _t[_index]; }

		Values& back() { return _t[1 ^ _index]; }

		void exchange() {
			_index ^= 1;
		}

		void push(const T& value) {
			_t[1 ^ _index].push_back(value);
		}

		template<class Iter>
		void insert(const Iter& first, const Iter& end) {
			auto& values = _t[1 ^ _index];
			values.insert(values.end(), first, end);
		}

		void inster(const Values& adds) {
			auto& values = _t[1 ^ _index];
			values.inster(values.end(), adds.begin(), adds.end());
		}
	};
}