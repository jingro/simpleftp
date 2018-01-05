#ifndef SIMPLEFTP_CMD_EXECUTOR_H
#define SIMPLEFTP_CMD_EXECUTOR_H

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

using std::string;
using std::unordered_map;
using std::stringstream;

class CmdExecutor {
private:
    string cmd;
    int cmd_index;
    unordered_map<string, int> commands;

protected:
    Socket *socket;
    int buffer_size;

public:
    CmdExecutor(Socket *socket);

    bool CheckCommand(string cmd);

    void Run();

    bool Exist(string path);

    virtual bool GetFile()=0;

    virtual bool PutFile()=0;

    virtual void RemoveFile()=0;

    virtual void MakeDirectory()=0;

    virtual void RemoveDirectory()=0;

    virtual void Rename()=0;

    virtual void ListFile()=0;
};


#endif //SIMPLEFTP_CMD_EXECUTOR_H
