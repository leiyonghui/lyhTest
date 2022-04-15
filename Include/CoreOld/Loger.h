#pragma once
#include <string>
#include <iostream>
#include "TimeHelp.h"

namespace core
{
	template<class ...Args>
	inline void printf_log(std::string time, const char* file, int line, Args ...args)
	{
		std::cout << time << " " << file << ":" << line;
		//((std::cout) << ... << (args <<" ")) << endl;//(cout << "1" << ( "2"<< ("3" << ("4" << "5"))));
		((std::cout << " " << args), ...) << std::endl;
	}

	template<class ...Args>
	inline void printf_info(Args ...args)
	{
		((std::cout << " " << args), ...) << std::endl;
	}

	inline const char* get_short_file(const char* file, size_t size)
	{
		for (size_t i = size - 2; i >= 0; --i)
		{
			switch (file[i]) { case '/': case '\\': return file + i + 1; };
		}
		return file;
	}


#define core_log_trace(...) printf_log(TimeHelp::TimeToString(time(NULL)), get_short_file(__FILE__, sizeof(__FILE__)), __LINE__, ## __VA_ARGS__);
#define core_log_error(...) printf_log(TimeHelp::TimeToString(time(NULL)), get_short_file(__FILE__, sizeof(__FILE__)), __LINE__, "ERROR", ## __VA_ARGS__);
#define core_log_warning(...) printf_log(TimeHelp::TimeToString(time(NULL)), get_short_file(__FILE__, sizeof(__FILE__)), __LINE__, "WARNING", ## __VA_ARGS__);
#define core_log_info(...) printf_info("INFO", ## __VA_ARGS__);

}
