#pragma once

class ObjectBase
{
public:
	ObjectBase(int v = 0, double db = 0.0):_value(v),_valueDb(db){}
	int _value;
	double _valueDb;
};

class ObjectA : public ObjectBase
{
public:
	ObjectA(int v1 = 0, double db1 = 0, int v2 = 0, double db2 = 0): ObjectBase(v1, db1),_valueA(v2),_valueDbA(db2)
	{

	}
	int _valueA;
	double _valueDbA;
};

class ObjectB : public ObjectA
{
public:
	ObjectB(){}

	int _valueB;
	double _valueDbB;
};

class ObjectC : public ObjectA, public ObjectB
{
public:
	ObjectC():ObjectA(),ObjectB(),_valueC(0),_valueDbC(0){}
	int _valueC;
	double _valueDbC;
};

class ObjectOther
{
public:
	ObjectOther():_valueO(0),_valueDbO(0){}
	int _valueO;
	double _valueDbO;
};

class ObjectTop : public ObjectOther, public ObjectA
{
public:
	ObjectTop() :_valueT(0), _valueDbT(0){}
	int _valueT;
	double _valueDbT;
};

void testObject();