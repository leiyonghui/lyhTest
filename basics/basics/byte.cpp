#include "core/types.h"
#include <iostream>

using namespace std;
using namespace core;
/*
ָ������ֵ��������ָ���Ķ���ֵ����ΪpackLen��
Ĭ�϶���ֵ���ṹ����ÿ�����ݳ�Ա���ṹ�屾����Ĭ�϶���ֵ����ΪdefaultLen��
��Աƫ������������ڽṹ����ʼλ�õĳ��ȣ���Ϊoffset��
��Ա���ȣ��ṹ����ÿ�����ݳ�Ա�ĳ��ȣ�ע�ṹ���ԱΪ����֮��ĳ��ȣ�����ΪmemberLen��
����������

������� offset % vaildLen = 0������vaildLenΪ��Ч����ֵvaildLen = min(packLen, defaultLen)��
������ ���Ա���������ض����������Ҫ���䲹�룻����ǰ�����һЩ�ֽڱ�֤�ó�Ա���롣�������ֽ�����Ϊpad
��������������������������������
��Ȩ����������ΪCSDN������OopspoO����ԭ�����£���ѭCC 4.0 BY-SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https://blog.csdn.net/cclethe/article/details/79659590
*/
//#pragma pack(1)
struct MyStruct
{
	uint8 hour; //[0,23]
	uint16 totalday; //index for extra info
	uint8 day; //[1,31]
	uint32 mon; //[0, 11] from January
	uint8 year; //[0,137] from 1900
};

#define PN(a) cout<<a<<endl;

#define PL(x,a,b) x.##a##b

struct STb
{
	int32 a1;
	int32 a2;
};

void kb(...)
{
	//printf("kb,,,%s\n");
}

void test2()
{
	STb tb;
	tb.a1 = 1;
	tb.a2 = 2;
	printf("%d\n", PL(tb, a, 1));
	printf("%d\n", PL(tb, a, 2));

	MyStruct *a, *b;
	MyStruct A, B;
	a = &A;
	b = &B;
	a->day = 2;
	a->hour = 2;
	a->mon = 2;
	a->year = 2;
	a->totalday = 2;

	PN(sizeof(MyStruct));
	PN((int64)(&((MyStruct*)0)->hour));
	PN((int64)(&((MyStruct*)0)->totalday));
	PN((int64)(&((MyStruct*)0)->day));
	PN((int64)(&((MyStruct*)0)->mon));
	PN((int64)(&((MyStruct*)0)->year)); 
	//PN((int64)(&a->day) - (int64)(&((MyStruct*)0)->day));
	//PN((int64)(&a->day) - (int64)(&((MyStruct*)0)->day));
	//PN(sizeof(a));
	//PN((unsigned char)&a->hour);
	//PN(&a->day);
	//PN(&a->mon);
	//PN(&a->year);
	//PN(&a->totalday);
	//PN(a->mon);
	//PN((int64)(&a->day));
	////PN((int64)(&((MyStruct*)0)->day));
	//MyStruct *c = (MyStruct *)((int64)(&a->day) - (int64)(&((MyStruct*)0)->day));
	//PN((int64)c);
	//PN(a->day);
	//cout << "==========" << (sizeof(a)) << "    "<<(sizeof(MyStruct));


	
	/*b->day = 1;
	b->hour = 2;
	b->mon = 2;
	b->year = 2;
	b->totalday = 3;*/

	//int c = *(const uint32 *)b - *(const uint32 *)a;
	//cout << "...." << c;

}
