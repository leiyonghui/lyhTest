#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<iostream>
using namespace std;

#define BUF_SIZE (4608  * 2 + 10)

int32 echoClient(char* ip, int32 port)
{
    int sock;
    char message[BUF_SIZE];
    int str_len;
    struct sockaddr_in serv_adr;

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(ip);
    serv_adr.sin_port = htons(port);

    if (connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect() error!");
    else
        puts("Connected...........");

    setBuffSize(sock, 10, 100);

    while (1)
    {
        //fputs("Input message(Q to quit): ", stdout);
        //fgets(message, BUF_SIZE, stdin);

        for (int32 i = 0; i< BUF_SIZE; i++)
        {
            message[i] = 1;
        }
        message[BUF_SIZE - 1] = 0;

        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;
        if (!strcmp(message, "!\n"))
        {
            assert(false);
        }
		if (!strcmp(message, "shut2\n"))
		{
			cout << "do shut2" << endl;
			if (::shutdown(sock, SHUT_RD))//
			{
				cout << "shutdown error" << endl;
			}
		}
        cout << "messagelen:" << strlen(message) << endl;
        while (true)
        {
            int32 cnt = write(sock, message, strlen(message));
            cout << "write:" << cnt << endl;
        }
        str_len = read(sock, message, BUF_SIZE - 1);
        message[str_len] = 0;
        printf("Message from server: %d , %s", str_len, message);
    }

    close(sock);
    return 0;
}