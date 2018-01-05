#ifndef SIMPLEFTP_CLIENT_CMD_EXECUTOR_H
#define SIMPLEFTP_CLIENT_CMD_EXECUTOR_H

#include <unordered_map>
#include <sys/stat.h>
#include "socket.h"
#include "client_socket.h"
#include "cmd_executor.h"

using std::unordered_map;
using std::endl;
using std::cin;

class ClientCmdExecutor : public CmdExecutor {
private:
    bool GetFile();

    bool PutFile();

    void RemoveFile();

    void MakeDirectory();

    void RemoveDirectory();

    void Rename();

    void ListFile();


public:
    ClientCmdExecutor(ClientSocket *socket);
};

#endif //SIMPLEFTP_CLIENT_CMD_EXECUTOR_H