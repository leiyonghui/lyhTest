#pragma once
#include "Configs.h"

namespace core
{
#define  BYTESWAP16(A) (((A&0xff00)>>8) | ((A&0x00ff)<<8))
#define  BYTESWAP32(A) \
	(((A&(0xff00'0000))>>24) | ((A&(0x00ff'0000))>>8) | \
	((A & 0x0000'ff00) << 8) | ((A & 0x0000'00ff) << 24))
#define  BYTESWAP64(A) \
		(((A&(0xff00'0000'0000'0000))>>56) | ((A&(0x00ff'0000'0000'0000))>>40) | \
		(((A&(0x0000'ff00'0000'0000))>>24) | ((A&(0x0000'00ff'0000'0000))>>8) | \
		((A&0x0000'0000'ff00'0000)<<8) | ((A&0x0000'0000'00ff'0000)<<24)) | \
		((A&0x0000'0000'0000'ff00)<<40) | ((A&0x0000'0000'0000'00ff)<<56))

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

	inline int CheckCPUendian()
	{
		union {
			unsigned long int i;
			unsigned char s[4];
		}c;

		c.i = 0x12345678;
		return (0x12 == c.s[0]);
	}

	inline uint64 hostToNetwrok64(uint64 host64)
	{
		return CheckCPUendian() ? host64 : BYTESWAP64(host64);//本地大端则与网络相同
	}

	inline uint32 hostToNetwork32(uint32 host32)
	{
		return CheckCPUendian() ? host32 : BYTESWAP32(host32);
	}

	inline uint16 hostToNetwork16(uint16 host16)
	{
		return CheckCPUendian() ? host16 : BYTESWAP16(host16);
	}

	inline int64 netwrokToHost64(uint64 net64)
	{
		return CheckCPUendian() ? net64 : BYTESWAP64(net64);
	}

	inline uint32 networkToHost32(uint32 net32)
	{
		return CheckCPUendian() ? net32 : BYTESWAP32(net32);
	}

	inline uint16 networkToHost16(uint16 net16)
	{
		return CheckCPUendian() ? net16 : BYTESWAP16(net16);
	}

	inline float hostToNetwrokfloat(float f)
	{
		IntWithfloat c;
		c._float = f;
		c._int = hostToNetwork32(c._int);
		return c._float;
	}

	inline double hostToNetwrokdouble(double d)
	{
		LongWithDouble c;
		c._double = d;
		c._long = hostToNetwrok64(c._long);
		return c._double;
	}

	inline float networkToHostfloat(float f)
	{
		IntWithfloat c;
		c._float = f;
		c._int = networkToHost32(c._int);
		return c._float;
	}

	inline double networkToHostdouble(double d)
	{
		LongWithDouble c;
		c._double = d;
		c._long = netwrokToHost64(c._long);
		return c._double;
	}
}

namespace core
{
	template< typename U, typename K, typename V>
	const U find(const std::map<K, V>& container, const K& key, const U& vaule)
	{
		auto iter = container.find(key);
		if (iter == container.end())
		{
			return vaule;
		}
		return iter->second;
	}
}