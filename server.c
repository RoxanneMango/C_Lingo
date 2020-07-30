#include "server.h"

void * 
server(void * void_lingo)
{
	Lingo * lingo = void_lingo;
	
	int listenfd;
	struct sockaddr_in servaddr;
	char * ip_address = SERVER_IP;
	int server_port = SERVER_PORT;
	
	create_socket(&listenfd, servaddr, ip_address, server_port);
	
	uint8_t buff[MAXLINE];
	uint8_t recvline[MAXLINE];
	
	char * message = calloc(MAXLINE, sizeof(char));
	
	int connfd;
	
	char * client_address = NULL;
	struct sockaddr_in addr;
	
	char * guess = calloc( lingo->guessesRemaining, sizeof(char) );
	
	Param param =
	{
		.key = calloc(15, sizeof(char)),
		.value = calloc(15, sizeof(char))
	};
	
	for(;;)
	{
		/* reset buffers */
		memset(recvline, 0, MAXLINE);
		memset(buff, 0, MAXLINE);
		memset(message, 0, MAXLINE);
		
		//printf("\nWaiting for connection\n"); fflush(stdout);
		connect_client(&connfd, &listenfd, addr, recvline, client_address);
		
		switch(checkRequestType((char *)recvline))
		{
			case GET:
			{
				//printRequestFirstLine((char *)recvline); printf("\n"); fflush(stdout);
				getPage((char *)recvline, message);
				getLingoVariable((char *)recvline, lingo, message);
				break;
			}
			case POST:
			{
				printParams((char *)recvline); fflush(stdout);
				if((get_key_and_value((char *)recvline, &param) < 0))
				{
					printf("Invalid { key : value } pair!\n");
				}		

				lingo_input(lingo, &param);
				buildLingoPage(lingo, message);
				
				break;
			}
			default:
			{
				err_n_die("Package type error.");
				break;
			}
		}
		
		
		snprintf( (char *)buff, sizeof(buff), "HTTP/1.0 200 OK\r\n\r\n%s", message);
		write(connfd, (char *)buff, strlen((char *)buff));
		close(connfd);
		
		//printf("\nConnection closed\n"); fflush(stdout);
	}
	
	free(guess);
	free(message);
	
	return NULL;
}

void
create_socket(int * listenfd, struct sockaddr_in servaddr, char * ip_address, int server_port)
{
	if( (*listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		err_n_die("Socket error.");
	}
	
	bzero(&servaddr, sizeof(servaddr));
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
