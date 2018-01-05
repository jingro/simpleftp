#ifndef __FTP__SOCKET__
#define __FTP__SOCKET__

#include <string>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>

typedef unsigned char byte;

using std::string;

class Socket {

private:
    int buffer_size;

protected:
    int socket_fd;

    struct sockaddr_in local_address;
    char local_ip[20];
    socklen_t local_port;

    struct sockaddr_in remote_address;
    char remote_ip[20];
    socklen_t remote_port;

    void ShowError(const char *);

public:

    Socket();

    void StartListen();

    int AcceptClient();

    void CloseSocket();

    void SetSocketFd(int socket_fd);

    void SendInt(int i);

    void ReceiveInt(int *i);

    void SendString(string str);

    void ReceiveString(string &str);

    void SendData(byte *data, size_t size);

    void ReceiveData(byte *data, size_t *size);

};

#endif
