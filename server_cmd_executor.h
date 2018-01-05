#ifndef SIMPLEFTP_SERVER_CMD_EXECUTOR_H
#define SIMPLEFTP_SERVER_CMD_EXECUTOR_H

#include <string>
#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <unordered_map>
#include <sys/stat.h>
#include <dirent.h>
#include <sstream>
#include "socket.h"
#include "server_socket.h"
#include "cmd_executor.h"

using std::string;
using std::unordered_map;
using std::stringstream;

class ServerCmdExecutor : public CmdExecutor {
private:
    string username;
    char cwd[128];

public:
    ServerCmdExecutor(ServerSocket *socket, string username);

    void ChangeToCWD();

    bool GetFile();

    bool PutFile();

    void ListFile();

    void RemoveFile();

    void MakeDirectory();

    void RemoveDirectory();

    void Rename();

    void Run();
};

#endif //SIMPLEFTP_SERVER_CMD_EXECUTOR_H