#pragma once
#include "headers.h"

enum EType
{

};

template<EType Name>
class CString
{
public:
	static EType name;
};

template<EType Name>
EType CString<Name>::name = Name;


template<const int* Name>
class CName
{
public:
	const static int* name;
};

template<const int* Name>
const int* CName<Name>::name = Name;