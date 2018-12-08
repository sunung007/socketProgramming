// TCP/IP Socket programming.
// Client

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
#define IP "127.0.0.1"
#define PORT 50000

// Make error message and kill the program
// when error occurs.
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
	// If the file named "received.txt" is already in directory, remove that file,
	// and create new file named "received.txt".
    if((file = open("received.txt", O_WRONLY | O_CREAT | O_EXCL, 0777)) == -1) {
        remove("received.txt");
        file = open("received.txt", O_WRONLY | O_CREAT, 0777);

        if(file == -1)
            error_handling("RECIEVE FILE OPEN ERROR");
    }

	// Socket programming
	// Outline: socket() -> connect() -> read() -> close()

	// Socket
    client_socket = socket(PF_INET, SOCK_STREAM, 0);
    if(client_socket == -1)
        error_handling("SOCKET OPEN ERROR");
 
	// Setting server socket.
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    // Connect with server.
    if(connect(client_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1)
        error_handling("CONNECTION ERROR");

    // Read and put in buffer.
    while((len = read(client_socket, buffer, BUFSIZE)) != 0)
        write(file, buffer, len);

    // If recieving file is done successfully, send "Thank you"
    // message to server.
    write(client_socket, "Thank you\n", 10);

	// Close file and socket.
    close(file);
    close(client_socket);
 
    return 0;
}
