#pragma once
/*用户自定义字面量运算符的参数（返回值随意），函数的参数必须是以下的类型
1、const char *
2、unsigned long long int
3、long double
4、char
5、wchar_t
6、char16_t
7、char32_t
8、const char * , std::size_t
9、const wchar_t * , std::size_t
10、 const char16_t * , std::size_t
11、const char32_t * , std::size_t
*/
bool operator"" _s(unsigned long long _Val)
{
    return _Val;
}