template<class T>
class Vector
{
	int countSize;//数组具体大小
	int capacity;//不定长数组大小
	T *p;

public:
	Vector():capacity(15),countSize(0) {
		p = new T[capacity];
	}

	~Vector() {
		delete[] p;
	}

	Vector(const Vector &vec) {
		*this = vec;
	}

	//增加不定长数组
	void AddSize(int newSize)
	{
		if (capacity > newSize)
			return;

		T *oldp = p;
		p= new T[newSize];
		for (int i = 0; i < countSize; i++)
		{
			p[i] = oldp[i];
		}

		capacity = newSize;
		delete[] oldp;
	}


	int size() const
	{
		return countSize;
	}

	int cap() const
	{
		return capacity;
	}

	int end() const
	{
		return countSize;
	}

	//insert
	void insert(int pos,const T &t)
	{
		if (pos<0 || pos>end())
			return;

		if (countSize + 1> capacity)
			AddSize(capacity*2+1);

		int i = countSize;
		while (i> pos)
		{
			p[i] = p[i - 1];
			i--;
		}
		p[pos] = t;
		countSize++;
	}

	//.erase
	int erase(int pos)
	{
		if (pos > size() || pos < 0)
			return end();

		int i = pos;
		while (i<countSize-1)
		{
			p[i] = p[i+1];
			i++;
		}
		countSize--;
		return pos;
	}

	//push_back
	void push_back(const T &v)
	{
		insert(countSize, v);
	}

	void push_back(T &&v)
	{
		insert(countSize, v);
	}

	void pop_back()
	{
		erase(countSize-1);
	}

	T& front() const
	{
		return p[0];
	}

	T& back() const
	{
		return p[countSize-1];
	}

	//重写[]
	T& operator[](int pos) {
		return p[pos];
	}

	//重写=
	Vector& operator=(const Vector &vec) {

		if (this == &vec)
			return *this;

		countSize = vec.size();
		capacity = vec.cap();
		delete[] p;
		p = new T[capacity];
		for (int i = 0; i < countSize; i++)
		{
			p[i] = vec.p[i];
		}

		return *this;
	}
};