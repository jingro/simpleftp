#include "cmd_executor.h"

CmdExecutor::CmdExecutor(Socket *socket) {
    this->socket = socket;
    commands["get"] = 0;
    commands["put"] = 1;
    commands["list"] = 2;
    commands["remove"] = 3;
    commands["mkdir"] = 4;
    commands["rmdir"] = 5;
    commands["rename"] = 6;
}

bool CmdExecutor::CheckCommand(string cmd) {
    buffer_size = 1024;
    if (commands.find(cmd) == commands.end())
        return false;
    cmd_index = commands[cmd];
    return true;
}

void CmdExecutor::Run() {
    string response;
    switch (cmd_index) {
        case 0:
            GetFile();
            break;
        case 1:
            PutFile();
            break;
        case 2:
            ListFile();
            break;
        case 3:
            RemoveFile();
            break;
        case 4:
            MakeDirectory();
            break;
        case 5:
            RemoveDirectory();
            break;
        case 6:
            Rename();
            break;
        default:
            cout << "wrong command" << endl;
    }
}

bool CmdExecutor::Exist(string path) {
    if (access(path.c_str(), F_OK) != 0)
        return false;
    return true;
}