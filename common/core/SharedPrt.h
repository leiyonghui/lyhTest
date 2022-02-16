#pragma once
#include <functional>
//����ָ��
//�����������໥ʹ��һ��shared_ptr��Ա����ָ��Է��������ѭ�����ã�ʹ���ü���ʧЧ���Ӷ������ڴ�й©��
template<class T>
class SharedPrt
{
public:
	T *pr;
	int *num;
	std::function<void (T*)> deleter;

	SharedPrt() :pr(nullptr), num(nullptr)
	{

	}

	SharedPrt(T *p) :pr(p)
	{
		num = new int(1);
	}

	SharedPrt(const SharedPrt &prt) :pr(prt.pr), num(prt.num) {// pass_by_reference_to_const
		if (num)
			*num = *num + 1;
	}

	SharedPrt(T *p, std::function<void (T*)> del):pr(p)
	{
		num = new int(1);
		deleter = del;
	}

	virtual ~SharedPrt()
	{
		if (num)
		{
			*num = *num - 1;
			if (*num == 0) {
				if (deleter!=nullptr)
					deleter(pr);
				else
					delete pr;
			}
		}
	}

	SharedPrt& operator=(SharedPrt &right) {

		if (num)
		{
			*num = *num - 1;
			if (*num == 0)
				delete pr;
		}
		pr = right.pr;
		num = right.num;
		*num = *num + 1;

		return *this;
	}

	T* get() const
	{
		return pr;
	}

	T& operator*() {
		return *pr;
	}

	const T* operator->() const {
		return pr;
	}

	T* operator->() {
		return pr;
	}

	int use_count() const
	{
		return *num;
	}
};
