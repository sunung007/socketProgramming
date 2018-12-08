// TCP/IP Socket programming.
// Server

// 2017029425 KimSunWoong 

// Develop enviroment
// ubuntu 18.04.1 LTS
// vim version 8.0.1453
// gcc option does not exist

// A file is sent from server to client. In server, the file to be sent
// is named with "sending.txt", and the file to be received is named
// with "received.txt".

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

// Make error message and kill the program
// when error occurs.
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
	// A file is sent from server to client. So I do not need to
	// set a permission like 0777.
    file = open("sending.txt", O_RDONLY);
    if(file == -1)
        error_handling("SEND FILE OPEN ERROR");
 
    // Make new socket with 6, which is TCP protocol.
    // The option is to prevent bind error. If I make socekt as soon as closing 
	// the socket, bind error ouccrs. So to prevent it, I must set option to socket.
	server_socket = socket(PF_INET, SOCK_STREAM, 6);
    option = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    if(server_socket == -1)
        error_handling("SOCKET OPEN ERROR");
 
	// Set a server socket.
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));

    // Bind
    if(bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        error_handling("BIND ERROR");

    // Listen. The second argument is maximum number of client.
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

	// Close file and sockets.
    close(file);
    close(client_socket);
    close(server_socket);

    return 0; 
}
