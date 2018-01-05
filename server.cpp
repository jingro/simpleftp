#include "socket.h"
#include "server_socket.h"
#include "server_cmd_executor.h"
#include <pthread.h>


const int PORT = 30000;
using namespace std;

void *ServerHandler(void *arg) {
    int client_socket_fd = *((int *) arg);
    free(arg);
    pthread_detach(pthread_self());
    ServerSocket *handler = new ServerSocket();
    handler->SetSocketFd(client_socket_fd);
    string username;
    handler->ReceiveString(username);
    ServerCmdExecutor *executor = new ServerCmdExecutor(handler, username);
    string cmd;
    while (true) {
        handler->ReceiveString(cmd);
        if (cmd == "quit") {
            handler->CloseSocket();
            break;
        }
        executor->CheckCommand(cmd);
        executor->Run();
    }
    delete executor;
    delete handler;
    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char *argv[]) {
    ServerSocket server(PORT);
    server.StartListen();
    cout << "Running......" << endl;
    char cwd[100];
    getcwd(cwd, sizeof(cwd));
    pthread_t thread_id;
    int *client_socket_fd;
    while (true) {
        cout << cwd << endl;
        chdir(cwd);
        client_socket_fd = (int *) malloc(sizeof(int));
        *client_socket_fd = server.AcceptClient();
        pthread_create(&thread_id, NULL, ServerHandler, client_socket_fd);
    }
    return 0;
}
