#include "client_cmd_executor.h"

ClientCmdExecutor::ClientCmdExecutor(ClientSocket *socket) : CmdExecutor(socket){
}


bool ClientCmdExecutor::PutFile() {
    string file_name;
    cout << "please input the filename: ";
    cin >> file_name;
    FILE *fp;
    if ((fp = fopen(file_name.c_str(), "rb")) == NULL)
        return false;

    //send file name via socket
    socket->SendString(file_name);

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
    delete[] buffer;
    cout << "put file " << file_name << " successfully and file size is: " << file_size << endl;
    return true;
}

bool ClientCmdExecutor::GetFile() {
    string file_name;
    cout << "please input the filename: ";
    cin >> file_name;
    FILE *fp;
    if ((fp = fopen(file_name.c_str(), "wb")) == NULL)
        return false;

    socket->SendString(file_name);

    //receive the file size firstly
    //to determine when to stop receive data
    int file_size;
    socket->ReceiveInt(&file_size);

    int count = 0;
    byte *buffer = new byte[buffer_size];
    memset(buffer, 0, sizeof(byte) * buffer_size);
    size_t size;
    while (count != file_size) {
        socket->ReceiveData(buffer, &size);
        count += fwrite(buffer, sizeof(byte), size, fp);
    }
    fclose(fp);
    cout << "get file " << file_name << " successfully and file size is: " << file_size << endl;
    delete[] buffer;
    return true;
}


void ClientCmdExecutor::RemoveFile() {
    string file_name, response;
    cout << "input the file name need remove: ";
    cin >> file_name;
    socket->SendString(file_name);
    socket->ReceiveString(response);
    cout << response << endl;
}

void ClientCmdExecutor::MakeDirectory() {
    string dir_name, response;
    cout << "input the directory name need to be created: ";
    cin >> dir_name;
    socket->SendString(dir_name);
    socket->ReceiveString(response);
    cout << response << endl;
}

void ClientCmdExecutor::RemoveDirectory() {
    string dir_name, response;
    cout << "input the directory name need to remove: ";
    cin >> dir_name;
    socket->SendString(dir_name);
    socket->ReceiveString(response);
    cout << response << endl;
}

void ClientCmdExecutor::Rename() {
    string old_name, new_name, response;
    cout << "input the file name need to rename: ";
    cin >> old_name;
    socket->SendString(old_name);
    cout << "input new file name: ";
    cin >> new_name;
    socket->SendString(new_name);
    socket->ReceiveString(response);
    cout << response << endl;
}

void ClientCmdExecutor::ListFile() {
    string response;
    socket->ReceiveString(response);
    cout << response << endl;
}