#ifndef SIMPLEFTP_SERVER_SOCKET_H
#define SIMPLEFTP_SERVER_SOCKET_H
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "socket.h"

#include <iostream>

typedef unsigned char byte;

using std::string;
using std::cout;
using std::endl;

class ServerSocket : public Socket {

private:
    int backlog;

public:
    ServerSocket(socklen_t local_port);

    ServerSocket();

    void StartListen();

    int AcceptClient();
};

#endif //SIMPLEFTP_SERVER_SOCKET_H