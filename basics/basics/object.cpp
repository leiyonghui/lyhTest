#include "object.h"
#include "configs.h"

#define PN(a) cout<<a<<endl;

namespace object
{
	void testObject()
	{
		ObjectBase base(1, 1.1);
		ObjectA objA(2, 2.1, 3, 3.1);
		ObjectB objB;
		objB._valueB = 2;
		objB._valueDbB = 2;

		ObjectA baseTmp = objB;
		cout << "bv = " << baseTmp._value << "   basedb = " << baseTmp._valueDb << endl;
		//printf("basev = %d ,  basedb = %f\n", baseTmp._value, baseTmp._valueDb);
		PN(sizeof(ObjectBase));
		PN((int64)(&((ObjectBase*)0)->_value));
		PN((int64)(&((ObjectBase*)0)->_valueDb));
		PN("-----------A");
		PN(sizeof(ObjectA));
		PN((int64)(&((ObjectA*)0)->_value));
		PN((int64)(&((ObjectA*)0)->_valueDb));
		PN((int64)(&((ObjectA*)0)->_valueA));
		PN((int64)(&((ObjectA*)0)->_valueDbA));
		PN("---------------B");
		PN(sizeof(ObjectB));
		PN((int64)(&((ObjectB*)0)->_value));
		PN((int64)(&((ObjectB*)0)->_valueDb));
		PN((int64)(&((ObjectB*)0)->_valueA));
		PN((int64)(&((ObjectB*)0)->_valueDbA));
		PN((int64)(&((ObjectB*)0)->_valueB));
		PN((int64)(&((ObjectB*)0)->_valueDbB));
		PN("--------------------C");
		PN(sizeof(ObjectC));
		PN((int64)(&((ObjectC*)0)->ObjectA::_value));
		PN((int64)(&((ObjectC*)0)->ObjectA::_valueDb));
		PN((int64)(&((ObjectC*)0)->ObjectA::_valueA));
		PN((int64)(&((ObjectC*)0)->ObjectA::_valueDbA));
		PN((int64)(&((ObjectC*)0)->_valueB));
		PN((int64)(&((ObjectC*)0)->_valueDbB));
		PN("------------------D");
		PN(sizeof(ObjectTop));
		PN((int64)(&((ObjectTop*)0)->_valueO));
		PN((int64)(&((ObjectTop*)0)->_valueDbO));
		PN((int64)(&((ObjectTop*)0)->_value));
		PN((int64)(&((ObjectTop*)0)->_valueDb));
		PN((int64)(&((ObjectTop*)0)->_valueA));
		PN((int64)(&((ObjectTop*)0)->_valueDbA));
		PN((int64)(&((ObjectTop*)0)->_valueT));
		PN((int64)(&((ObjectTop*)0)->_valueDbT));
		PN("---------------O");
		PN((int64)(&((ObjectOther*)0)->_valueO));
		PN((int64)(&((ObjectOther*)0)->_valueDbO));
		ObjectTop top;
		top._value = 5;
		top._valueA = 6;
		ObjectA* other = &top;
		//PN(other->_valueA);
		cout << "=============" << endl;
		PN((int64)(&((ObjectS*)0)->_value));
		PN((int64)(&((ObjectS*)0)->_valueDb));
		PN((int64)(&((ObjectS*)0)->_valueO));
		PN((int64)(&((ObjectS*)0)->_valueDbO));
		cout << "*****************" << endl;
		ObjectS ob;
		ob._value = 1;
		ob._valueDb = 1.1;
		ob._valueO = 2;
		ob._valueDbO = 2.2;
		void* p = &ob;
		PN((int64)(p));
		PN((int64)(&ob));

		ObjectOther* p1;

		PN("--1--");
		p1 = (ObjectOther*)p;
		PN((int64)(p1));
		PN(p1->_valueO);// = 1

		PN("--2--");
		p1 = static_cast<ObjectOther*>(p);
		PN((int64)(p1));
		PN(p1->_valueO);// = 1

		PN("--3--");
		p1 = static_cast<ObjectOther*>((ObjectS*)(p));
		PN((int64)(p1));
		PN(p1->_valueO);// = 2

		PN("--4--");
		p1 = &ob;//发生转型
		PN((int64)(p1));
		PN(p1->_valueO); // = 2

		PN("--5--");
		p1 = static_cast<ObjectOther*>(&ob);
		PN((int64)(p1));
		PN(p1->_valueO);// = 2

		PN(p1->_valueDbO);

		ObjectOther O = ob;//调用 ObjectOther(const ObjectOther& o)拷贝构造
		PN(O._valueO);
	}
}

