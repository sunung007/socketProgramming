// 2017029425 Kim Sun Woong
// Computer software engineering department, Hanyang univ.

// tcpServer.c
// Server in TCP, TCP/IP protocol

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFSIZE 257

int main() {
	int serv_sd;
	int clnt_sd;
	int fd;
	char buf[BUFSIZE];

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	int clnt_addr_size;
	int len;

	// File open.
	fd = open("file_server.c", O_RDONLY);

	serv_sd = socket(PF_INET, SOCK_STREAM, 0);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	bind(serv_sd, ( struct sockaddr * )&serv_addr, sizeof(serv_addr));
	listen(serv_sd, 5);


	clnt_addr_size = sizeof(clnt_addr);
	clnt_sd = accept(serv_sd,
					 ( struct sockaddr * )&clnt_addr,
					 &clnt_addr_size);
	
	// Send a file to client.
	while ( ( len = read(fd, buf, BUFSIZE) ) != 0 ) {
		write(clnt_sd, buf, len);
	}

	//  End file sending, and close output stream.
	if ( shutdown(clnt_sd, SHUT_WR) == -1 ) {
		error_handling("shutdown() error");
	}

	// Import message "Thank you" from client.
	len = read(clnt_sd, buf, BUFSIZE);
	write(1, buf, len); // Write the messeage on console.

	close(fd);
	close(clnt_sd);

    return 0;
}