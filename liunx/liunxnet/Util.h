#pragma once
#include "Configs.h"
#include <endian.h>

inline uint64 honstToNetwork64(uint64 host64)
{
	return ::htobe64(host64);
}

uint32 honstToNetwork32(uint32 host32);

uint16 hostToNetwork16(uint16 host16);

uint64 networkToHost64(uint64 net64);

uint32 networkToHost32(uint32 net32);

uint16 networkToHost16(uint16 net16);