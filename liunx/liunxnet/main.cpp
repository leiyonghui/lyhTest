#include "headers.h"

int main(int argc, char ** argv)
{
    if (argc == 2) {
        echoEpollServ(atoi(argv[1]));
    }
    if (argc == 3) {
        echoClient(argv[1], atoi(argv[2]));
    }
    return 0;
}