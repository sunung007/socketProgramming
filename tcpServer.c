// 2017029425 Kim Sun Woong
// Computer software engineering department, Hanyang univ.

// tcpServer.c
// Server in TCP, TCP/IP protocol

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <winsock.h>


int main() {
	SOCKET sock, clinetSock;

	int serv_sd;
	int clnt_sd;
	int fd;
	char buf[BUFSIZE];

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	int clnt_addr_size;
	int len;

	fd = open("file_server.c", O_RDONLY); //ÆÄÀÏ¿ÀÇÂ

	serv_sd = socket(PF_INET, SOCK_STREAM, 0);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	bind(serv_sd, ( struct sockaddr * )&serv_addr,
		 sizeof(serv_addr));
	listen(serv_sd, 5);




    return 0;
}