//智能指针
template<class T>
class SharedPrt
{
public:
	T *pr;
	int *num;

	SharedPrt():pr(nullptr), num(nullptr)
	{

	}

	SharedPrt(T *p):pr(p)
	{
		num = new int;
		*num = 1;
	}

	SharedPrt(SharedPrt &prt):pr(prt.pr), num(prt.num) {
		if (num)
			*num = *num + 1;
	}

	~SharedPrt()
	{
		if (num)
		{
			*num = *num - 1;
			if (*num == 0) {
				delete pr;
			}
		}
	}

	SharedPrt& operator=(SharedPrt &right) {

		if (num)
		{
			*num = *num - 1;
			if(*num ==0)
				delete pr;
		}

		*right.num = *right.num + 1;
		pr = right.pr;
		num = right.num;

		return *this;
	}

	T& operator*() {
		return *pr;
	}

	T* operator->() {
		return pr;
	}
};
