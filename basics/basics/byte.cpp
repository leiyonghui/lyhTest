#include "core/types.h"
#include <iostream>

using namespace std;
using namespace core;
/*
指定对齐值：代码中指定的对齐值，记为packLen；
默认对齐值：结构体中每个数据成员及结构体本身都有默认对齐值，记为defaultLen；
成员偏移量：即相对于结构体起始位置的长度，记为offset；
成员长度：结构体中每个数据成员的长度（注结构体成员为补齐之后的长度），记为memberLen。
及两个规则：

对齐规则： offset % vaildLen = 0，其中vaildLen为有效对齐值vaildLen = min(packLen, defaultLen)；
填充规则： 如成员变量不遵守对齐规则，则需要对其补齐；在其前面填充一些字节保证该成员对齐。需填充的字节数记为pad
————————————————
版权声明：本文为CSDN博主「OopspoO」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/cclethe/article/details/79659590
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
