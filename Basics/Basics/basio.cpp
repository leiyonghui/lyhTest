#include "Configs.h"
#include <boost/asio.hpp>

using namespace std;

asio::io_service service[2];


void run(int32 i)
{
	service[1].run();
}

auto getThreadId()
{
	return std::this_thread::get_id();
}

void asioTest()
{

	asio::ip::tcp::socket sock1(service[0]);
	//boost::asio::ip::tcp::socket sock2(service[1]);
	//sock1.async_connect(ep, connect_handler);
	//sock2.async_connect(ep, connect_handler);
	//asio::deadline_timer t(service[0], boost::posix_time::seconds(1));
	//t.async_wait(run);

	
}