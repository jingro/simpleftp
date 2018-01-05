#include "client_socket.h"


ClientSocket::ClientSocket(const string remote_ip, const socklen_t remote_port) {
    this->remote_port = remote_port;
    strcpy(this->remote_ip, remote_ip.c_str());

    this->remote_address.sin_family = AF_INET;
    inet_aton(remote_ip.c_str(), (struct in_addr *)&remote_address.sin_addr);
    this->remote_address.sin_port = htons(this->remote_port);
    bzero(this->remote_address.sin_zero, 8);

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        ShowError("create socket error");
    }
}

void ClientSocket::StartConnection() {
    if (connect(socket_fd, (struct sockaddr *) &remote_address, sizeof(struct sockaddr)) == -1) {
        ShowError("connect error");
    }
}

