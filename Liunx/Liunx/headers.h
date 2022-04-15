#pragma once
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Configs.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>


inline void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int32 echoClient(char* ip, int32 port);

int32 echoEpollServ(int32 port);

inline void setBuffSize(int32 fd, int32 sends, int32 reads)
{
	using namespace std;

	auto state = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (void*)&sends, sizeof(sends));
	if (state)
	{
		std::cout << "set read error!" << std::endl;
	}
	state = setsockopt(fd, SOL_SOCKET, SO_RCVBUF, (void*)&reads, sizeof(reads));
	if (state)
	{
		std::cout << "set rcv error!" << std::endl;
	}
	socklen_t len = sizeof(sends);
	state = getsockopt(fd, SOL_SOCKET, SO_SNDBUF, (void*)&sends, &len);
	cout << " sendsize: " << sends << endl;

	state = getsockopt(fd, SOL_SOCKET, SO_SNDBUF, (void*)&reads, &len);
	cout << " readsize: " << reads << endl;
}