#include "socket.h"
#include "client_socket.h"
#include "client_cmd_executor.h"

#define PORT 30000

using std::string;
using std::cout;
using std::cin;
using std::endl;

//split username and ip from the command parameter
bool ParseCmdParameter(int argc, char *argv[], string &ip, string &username) {
    if (argc != 2) {
        cout << "wrong parameter:" << endl;
        cout << "please add command parameter of username and ip address" << endl;
        cout << "like root@127.0.0.1" << endl;
        return false;
    }
    string str = argv[1];
    int index = str.find("@");
    if (index == str.npos) {
        cout << "wrong parameter format" << endl;
        return false;
    }
    username = str.substr(0, index);
    ip = str.substr(index + 1, str.size() - index - 1);
    return true;
}

int main(int argc, char *argv[]) {
    string ip, username;
    if (!ParseCmdParameter(argc, argv, ip, username))
        return 1;
//    cout << ip << " " << username << endl;
    ClientSocket *client = new ClientSocket(ip, PORT);
    client->StartConnection();

    //send username to server to change
    //work directory after create connection
    //before operation
    client->SendString(username);
//    cout << "already send username to server" << endl;

    string input, output;
    ClientCmdExecutor *executor = new ClientCmdExecutor(client);
    while (true) {
        cout << "ftp> ";
        cin >> input;
        client->SendString(input);
        if (input == "quit") {
            client->CloseSocket();
            break;
        }
        if (!executor->CheckCommand(input)) {
            cout << "wrong command" << endl;
            continue;
        }
        executor->Run();
    }
    delete executor;
    delete client;
    return 0;
}