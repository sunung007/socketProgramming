// TCP/IP Socket programming.
// Server

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
 
void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
 
int main(int argc, char **argv) {
    int file;
    int server_socket, client_socket;     
    struct sockaddr_in server_addr, client_addr;
    int option;
     
    int len;
    int client_addr_size;
    char buffer[BUFSIZE];
 
    if(argc != 2)
        error_handling("Format : server [port]");

    // Open file to send.
    file = open("sending.txt", O_RDONLY);
    if(file == -1)
        error_handling("SEND FILE OPEN ERROR");
 
    // socket(), bind(), listen(), and accept() return -1 when errors occur.

    // Make new socket with 6, which is TCP protocol.
    server_socket = socket(PF_INET, SOCK_STREAM, 6);
    option = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    if(server_socket == -1)
        error_handling("SOCKET OPEN ERROR");
 
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));

    // Bind.
    if(bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        error_handling("BIND ERROR");

    // Listen. Second argument is maximum number of client.
    if(listen(server_socket, 5) == -1)
        error_handling("LISTEN ERROR");

    // Accept. To accept, first find client socket's size.
    client_addr_size = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &client_addr_size);
    if(client_socket == -1)
        error_handling("ACCEPT ERROR");
 
    // Send a file to client.
    while((len = read(file, buffer, BUFSIZE)) != 0)
        write(client_socket, buffer, len);

    // End file sending, and close output stream.
    if(shutdown(client_socket, SHUT_WR) == -1)
        error_handling("SHUTDOWN ERROR");

    // Recieve "Thank you" message from client.
    len = read(client_socket, buffer, BUFSIZE);
    write(1, buffer, len);

    close(file);
    close(client_socket);
    close(server_socket);

    return 0; 
}