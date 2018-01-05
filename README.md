# simple ftp

## simple implemetation of ftp

it involves of server and client and can transfer information and files between server and client
via socket

only several basic command are available currently
including:
- get: to fetch file in server and download it to current client working directory
- put: to upload file to server in client's current working directory
- list: to list all files and diretorys in server
- remove: to remove the specific file in server
- rmdir: to remove the specific directory in server
- mkdit: to create a diretory in server
- quit: to disconnect with server

## How to start:
1. run ./server to start server service in remote machine or local machine. current server port is 30000, and it might requires to open the port otherwise the client can't connect to server
2. run ./clinet with command parameter of username@address like tom@127.0.0.1 (ps. without parameter it can't work out), username specify the directory in server to operate
3. type in the above command to operate files and directorys (ps. command with paramete are not supported yet, but with prompts to specify parameter)
