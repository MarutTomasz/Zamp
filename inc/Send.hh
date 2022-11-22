#ifndef SEND_HH
#define SEND_HH



#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <iostream>

using namespace std;


int Send(int Socket2Serv, const char *sMesg);

#endif
