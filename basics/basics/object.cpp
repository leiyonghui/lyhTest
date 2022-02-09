#include "stdio.h"
#include "object.h"
#include <iostream>
#include "core/types.h"
using namespace std;
using namespace core;

#define PN(a) cout<<a<<endl;

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
	PN("-----------");
	PN(sizeof(ObjectA));
	PN((int64)(&((ObjectA*)0)->_value));
	PN((int64)(&((ObjectA*)0)->_valueDb));
	PN((int64)(&((ObjectA*)0)->_valueA));
	PN((int64)(&((ObjectA*)0)->_valueDbA));
	PN("---------------");
	PN(sizeof(ObjectB));
	PN((int64)(&((ObjectB*)0)->_value));
	PN((int64)(&((ObjectB*)0)->_valueDb));
	PN((int64)(&((ObjectB*)0)->_valueA));
	PN((int64)(&((ObjectB*)0)->_valueDbA));
	PN((int64)(&((ObjectB*)0)->_valueB));
	PN((int64)(&((ObjectB*)0)->_valueDbB));
	PN("--------------------");
	PN(sizeof(ObjectC));
	/*PN((int64)(&((ObjectC*)0)->_value));
	PN((int64)(&((ObjectC*)0)->_valueDb));
	PN((int64)(&((ObjectC*)0)->_valueA));
	PN((int64)(&((ObjectC*)0)->_valueDbA));
	PN((int64)(&((ObjectC*)0)->_valueB));
	PN((int64)(&((ObjectC*)0)->_valueDbB));*/
	PN("------------------");
	PN(sizeof(ObjectTop));
	PN((int64)(&((ObjectTop*)0)->_valueO));
	PN((int64)(&((ObjectTop*)0)->_valueDbO));
	PN((int64)(&((ObjectTop*)0)->_value));
	PN((int64)(&((ObjectTop*)0)->_valueDb));
	PN((int64)(&((ObjectTop*)0)->_valueA));
	PN((int64)(&((ObjectTop*)0)->_valueDbA));
	PN((int64)(&((ObjectTop*)0)->_valueT));
	PN((int64)(&((ObjectTop*)0)->_valueDbT));
	ObjectTop top;
	top._value = 5;
	top._valueO = 6;
	ObjectOther other = top;
	PN(other._valueO);
}
