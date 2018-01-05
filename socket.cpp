#include "socket.h"
using namespace std;

Socket::Socket() {
    buffer_size = 1024;
    socket_fd = -1;
}

void Socket::CloseSocket() {
    close(socket_fd);
}

void Socket::ShowError(const char *error) {
    perror(error);
    exit(-1);
}

void Socket::SetSocketFd(int socket_fd) {
    this->socket_fd = socket_fd;
}

void Socket::SendInt(int i) {
    if (send(socket_fd, &i, sizeof(int), 0) ==
        -1) {
        ShowError("send data error");
    }
}

void Socket::ReceiveInt(int *i) {
    if (recv(socket_fd, i, sizeof(int), 0) == -1) {
        ShowError("receive data error");
    }
}


void Socket::SendString(string str) {
    int str_size = str.size();
    SendInt(str_size);

    if (send(socket_fd, str.c_str(), str_size, 0) == -1) {
        ShowError("send data error");
    }
};

void Socket::ReceiveString(string &str) {
    int str_size = 0;
    ReceiveInt(&str_size);

    char buffer[buffer_size];
    memset(buffer, 0, sizeof(buffer));
    if (recv(socket_fd, buffer, str_size, 0) == -1) {
        ShowError("receive data error");
    }

    //update remote ip and port after receive data
//    strcpy(remote_ip, inet_ntoa(remote_address.sin_addr));
//    remote_port = ntohs(remote_address.sin_port);
    str = string(buffer);
}


void Socket::SendData(byte *data, size_t data_size) {

    if (send(socket_fd, &data_size, sizeof(data_size), 0) == -1) {
        ShowError("send data error");
    }

    if (send(socket_fd, data, data_size, 0) == -1) {
        ShowError("send data error");
    }
};

void Socket::ReceiveData(byte *data, size_t *size) {
    size_t data_size = 0;
    if (recv(socket_fd, &data_size, sizeof(data_size), 0) == -1) {
        ShowError("send data error");
    }
    *size = data_size;

//    byte buffer[buffer_size];
//    memset(buffer, 0, sizeof(buffer));
    if (recv(socket_fd, data, data_size, 0) == -1) {
        ShowError("send data error");
    }

    //update remote ip and port after receive data
//    strcpy(remote_ip, inet_ntoa(remote_address.sin_addr));
//    remote_port = ntohs(remote_address.sin_port);
}
