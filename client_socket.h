#ifndef SIMPLEFTP_CLIENT_SOCKET_H
#define SIMPLEFTP_CLIENT_SOCKET_H
#include <iostream>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include "socket.h"

using std::string;
using std::cout;

class ClientSocket : public Socket {

public:
    ClientSocket(const string remote_ip, const socklen_t remote_port);

    void StartConnection();
};

#endif //SIMPLEFTP_CLIENT_SOCKET_H
