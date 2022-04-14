#include "Address.h"

namespace network
{
	CAddress::CAddress():_ip(0), _port(0){
	}

	CAddress::CAddress(uint32 ip, uint16 port)
	{
	}

	CAddress::CAddress(std::string ip, uint16 port)
	{
	}

	CAddress::CAddress(const CAddress& address)
	{
	}


}
