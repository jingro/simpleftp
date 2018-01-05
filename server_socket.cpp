#include "server_socket.h"

ServerSocket::ServerSocket(socklen_t local_port) {
    backlog = 10;

    this->local_port = local_port;

    this->local_address.sin_family = AF_INET;
    this->local_address.sin_addr.s_addr = INADDR_ANY;
    this->local_address.sin_port = htons(this->local_port);
    bzero(this->local_address.sin_zero, 8);

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        ShowError("create socket error");
    }
}

ServerSocket::ServerSocket() {
}


//bind the port with and start listening
void ServerSocket::StartListen() {
    if (bind(this->socket_fd, (struct sockaddr *) &local_address, sizeof(struct sockaddr)) == -1) {
        ShowError("bind error");
    }

    if (listen(socket_fd, backlog) == -1) {
        ShowError("listen error");
    }
}

int ServerSocket::AcceptClient() {
    int client_socket_fd;
    struct sockaddr_in remote_address;
    socklen_t remote_address_len;
    if ((client_socket_fd = accept(socket_fd, (sockaddr *) &remote_address, &remote_address_len)) == -1) {
        ShowError("accept client error");
    }
    return client_socket_fd;
}
