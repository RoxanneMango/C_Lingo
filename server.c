#include "server.h"

void
create_socket(int * listenfd, struct sockaddr_in servaddr, char * ip_address, int server_port)
{
	if( (*listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		err_n_die("Socket error.");
	}
	memset(&servaddr, 0, sizeof(struct sockaddr_in));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(ip_address);
	servaddr.sin_port = htons(server_port);
	
	if( (bind(*listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr))) < 0 )
	{
		servaddr.sin_addr.s_addr = inet_addr(LOCALHOST);
		ip_address = LOCALHOST;
		server_port += 1;
		servaddr.sin_port = htons(server_port);
		
		if( (bind(*listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr))) < 0 )
		{
			err_n_die("Bind error.");
		}
	}
	
	if( (listen(*listenfd, 10)) < 0 )
	{
		err_n_die("Listen error.");
	}	
}

void
connect_client(int * connfd, int * listenfd, struct sockaddr_in addr, uint8_t * recvline, char * client_address)
{
	socklen_t addr_len;
	if( (*connfd = accept(*listenfd, (struct sockaddr *) &addr, &addr_len ) ) < 0 )
	{
		err_n_die("Connection error.");
	}

	//printf("client address: %s\n", inet_ntoa(addr.sin_addr));

	if( read(*connfd, recvline, MAXLINE-1) < 0 )
	{
		err_n_die("Read error.");
	}
}

void
write_socket(int connfd, char * buffer)
{
	write(connfd, (char *)buffer, strlen((char *)buffer));
}