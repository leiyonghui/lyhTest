#include "headers.h"
#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
    char* ip;
    int port;
    int iss = 0;
    cin >> iss;
    if (argc == 2 || iss == 1) {
		//if (iss)
		//	cin >> port;
		//else
		//	port = atoi(argv[1]);
        echoEpollServ(port);
    }
    if (argc == 3 || iss == 2) {
      //  if (iss)
      //  {
      //      cin >> ip >> port;
      //  }
      //  else
      //  {
      //      ip = argv[1];
		    //port = atoi(argv[2]);
      //  }
        echoClient(ip, port);
    }
    return 0;
}