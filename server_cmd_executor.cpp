#include "server_cmd_executor.h"

ServerCmdExecutor::ServerCmdExecutor(ServerSocket *socket, string username) : CmdExecutor(socket) {
    if (!Exist(username)) {
        mkdir(username.c_str(), 0755);
        cout << username << " dir does not exist" << endl;
    }
    chdir(username.c_str());
    this->username = username;
    //store the current user's working directory
    //thus when get command of the user it could
    //change to the appropriate directory
    getcwd(cwd, sizeof(cwd));
}


bool ServerCmdExecutor::GetFile() {
    string file_name;
    socket->ReceiveString(file_name);
    cout << "client retrieve file: " << file_name << endl;

    FILE *fp;
    if ((fp = fopen(file_name.c_str(), "rb")) == NULL)
        return false;

    //calculate the file size and
    //send size of the file via socket before send the file
    int file_size;
    fseek(fp, 0L, SEEK_END);
    file_size = ftell(fp);
    rewind(fp);
    socket->SendInt(file_size);

    byte *buffer = new byte[buffer_size];
    memset(buffer, 0, sizeof(byte) * buffer_size);
    int len;
    while (!feof(fp)) {
        len = fread(buffer, sizeof(byte), buffer_size, fp);
        socket->SendData(buffer, len);
    }
    fclose(fp);
    cout << "transfer file " << file_name << " successfully and file size is: " << file_size << endl;
    delete[] buffer;
    return true;
}

bool ServerCmdExecutor::PutFile() {
    string file_name;
    socket->ReceiveString(file_name);

    //receive the file size firstly
    //to determine when to stop receive data
    int file_size;
    socket->ReceiveInt(&file_size);

    int count = 0;
    FILE *fp;
    if ((fp = fopen(file_name.c_str(), "wb")) == NULL)
        return false;

    byte *buffer = new byte[buffer_size];
    memset(buffer, 0, sizeof(byte) * buffer_size);
    size_t size;
    while (count != file_size) {
        socket->ReceiveData(buffer, &size);
        count += fwrite(buffer, sizeof(byte), size, fp);
    }
    fclose(fp);
    delete[] buffer;
    cout << "transfer file " << file_name << " successfully and file size is: " << file_size << endl;
    return true;
}

void ServerCmdExecutor::RemoveFile() {
    string file_name;
    socket->ReceiveString(file_name);
    if (!Exist(file_name))
        socket->SendString("file does not exist");
    remove(file_name.c_str());
    socket->SendString("file remove successfully");
}

void ServerCmdExecutor::MakeDirectory() {
    string dir_name;
    socket->ReceiveString(dir_name);
    if (Exist(dir_name)) {
        socket->SendString("directory already exist");
        return;
    }
    mkdir(dir_name.c_str(), 0755);
    socket->SendString("directory created successfully");
}

void ServerCmdExecutor::RemoveDirectory() {
    string dir_name;
    socket->ReceiveString(dir_name);
    if (!Exist(dir_name)) {
        socket->SendString("directory does not exist");
        return;
    }
    rmdir(dir_name.c_str());
    socket->SendString("directory remove successfully");
}

void ServerCmdExecutor::Rename() {
    string old_name, new_name;
    socket->ReceiveString(old_name);
    if (!Exist(old_name)) {
        socket->SendString("file does not exist");
        return;
    }
    socket->ReceiveString(new_name);
    rename(old_name.c_str(), new_name.c_str());
    socket->SendString("file renamed successfully");
}

void ServerCmdExecutor::ListFile() {
    string response;
    stringstream ss(response);

    DIR *dirp;
    struct dirent *direntp;
    dirp = opendir(".");
    if (dirp) {
        while (true) {
            direntp = readdir(dirp);
            if (!direntp)
                break;
            else if (direntp->d_name[0] != '.')
                ss << direntp->d_name << " ";
        }
        closedir(dirp);
    }
    socket->SendString(ss.str());
}

void ServerCmdExecutor::ChangeToCWD() {
    chdir(cwd);
}

void ServerCmdExecutor::Run() {
    ChangeToCWD();
    CmdExecutor::Run();
}