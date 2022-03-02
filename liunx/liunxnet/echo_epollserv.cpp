#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <iostream>
#include <sstream>
#include <signal.h>

using namespace std;

#define BUF_SIZE 100
#define EPOLL_SIZE 50

void printEvent(int32 fd, int32 ev)
{
    std::ostringstream oss;
    oss << "fd:" << fd << " "<<ev<<" events:";
    if (ev & EPOLLIN)
        oss << "IN ";
    if (ev & EPOLLPRI)
        oss << "PRI ";
    if (ev & EPOLLOUT)
        oss << "OUT ";
    if (ev & EPOLLHUP)
        oss << "HUP ";
    if (ev & EPOLLRDHUP)
        oss << "RDHUP ";
    if (ev & EPOLLERR)
        oss << "ERR ";
    if (ev & EPOLLRDHUP)
        oss << "NVAL ";
    std::string str = oss.str();
    printf("%s\n", str.c_str());
}

void si(int p)
{
    cout << "-====" << endl;
}

int32 echoEpollServ(int32 port)
{
    signal(SIGPIPE, si);
  
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t adr_sz;
    int str_len, i;
    char buf[BUF_SIZE];

    struct epoll_event* ep_events;
    struct epoll_event event;
    int epfd, event_cnt;


    serv_sock = socket(PF_INET, SOCK_STREAM, 0);

	int32 optval = 1;
	::setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR,
		&optval, static_cast<socklen_t>(sizeof optval));

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(port);

    if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    epfd = epoll_create(EPOLL_SIZE);
    ep_events = (struct epoll_event*)malloc(sizeof(struct epoll_event) * EPOLL_SIZE);

    event.events = EPOLLIN;
    event.data.fd = serv_sock;
    epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &event);
    cout << "--start--"<< port << endl;
    while (1)
    {
        event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
        if (event_cnt == -1)
        {
            puts("epoll_wait() error");
            break;
        }

        for (i = 0; i < event_cnt; i++)
        {
            const auto& ev = ep_events[i];
            cout << endl;
            printEvent(ep_events[i].data.fd, ev.events);
            if (ep_events[i].data.fd == serv_sock)
            {
                adr_sz = sizeof(clnt_adr);
                clnt_sock =
                    accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
                event.events = EPOLLIN;
                event.data.fd = clnt_sock;
                epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sock, &event);
                printf("connected client: %d \n", clnt_sock);
            }
            else if(ev.events & EPOLLIN)
            {
                str_len = read(ep_events[i].data.fd, buf, BUF_SIZE);
                cout << " -- in:" << str_len << endl;
                if (str_len == 0)    // close request!
                {
                    epoll_ctl(
                        epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
                    close(ep_events[i].data.fd);
                    printf("closed client: %d \n", ep_events[i].data.fd);
                }
                else if(str_len > 0)
                {
                    write(ep_events[i].data.fd, buf, str_len);    // echo!
                }
                else 
                {
                    write(ep_events[i].data.fd, "122", 3);
					cout << "errno: " << errno << endl;
                }
            }
            else if (ev.events & EPOLLOUT)
            {
            }
        }
    }
    close(serv_sock);
    close(epfd);
    return 0;
}
