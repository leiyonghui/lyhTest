#pragma once
#include "core/Configs.h"
#include "object.h"

union IntWithfloat
{
	uint32 _int;
	float _float;
};

union LongWithDouble
{
	uint64 _long;
	double _double;
};

#define  BYTESWAP16(A) (((A&0xff00)>>8) | ((A&0x00ff)<<8))
#define  BYTESWAP32(A) \
	(((A&(0xff00'0000))>>24) | ((A&(0x00ff'0000))>>8) | \
	((A & 0x0000'ff00) << 8) | ((A & 0x0000'00ff) << 24))
#define  BYTESWAP64(A) \
		(((A&(0xff00'0000'0000'0000))>>56) | ((A&(0x00ff'0000'0000'0000))>>40) | \
		(((A&(0x0000'ff00'0000'0000))>>24) | ((A&(0x0000'00ff'0000'0000))>>8) | \
		((A&0x0000'0000'ff00'0000)<<8) | ((A&0x0000'0000'00ff'0000)<<24)) | \
		((A&0x0000'0000'0000'ff00)<<40) | ((A&0x0000'0000'0000'00ff)<<56))

using int32 = int;
using int64 = long long int;

void testUpper();

void testhton();