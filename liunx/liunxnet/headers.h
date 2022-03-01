#pragma once
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Configs.h"


inline void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int32 echoClient(char* ip, int32 port);

int32 echoEpollServ(int32 port);