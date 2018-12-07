// TCP/IP Socket programming.
// Client

// 2017029425 KimSunWoong 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
  
#define BUFSIZE 2048
#define IP "127.0.0.1"
#define PORT 50000
 
void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
 
int main(int argc, char **argv) {
    int file;
    int client_socket;
    struct sockaddr_in server_addr;
     
    int len;
    char buffer[BUFSIZE];
 
    if(argc != 3)
        error_handling("Format : client [IP address] [port number]");

    // File open to be saved a file that will be recieve from server.
    if((file = open("received.txt", O_WRONLY | O_CREAT | O_EXCL, 0777)) == -1) {
        remove("received.txt");
        file = open("received.txt", O_WRONLY | O_CREAT, 0777);

        if(file == -1)
            error_handling("RECIEVE FILE OPEN ERROR");
    }

    client_socket = socket(PF_INET, SOCK_STREAM, 0);
    if(client_socket == -1)
        error_handling("SOCKET OPEN ERROR");
 
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    // Connect.
    if(connect(client_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1)
        error_handling("CONNECTION ERROR");

    // Read.
    while((len = recv(client_socket, buffer, BUFSIZE, 0)) != 0)
        write(file, buffer, len);

    // If recieving file is done successfully, send "Thank you"
    // message to server.
    write(client_socket, "Thank you\n", 10);

    close(file);
    close(client_socket);
 
    return 0;
}