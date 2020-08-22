#include "server.h"

// TESTS:
/*
1. Check for buffer overflows: When receiving and sending data, and when reading in files!
	Increment counter when FP++ ; if (counter > MAXLINE) { err_n_die("Buffer overflow"); }
2. Check whether the files you try to open actually exist.

*/


int
main(int argc, char ** argv)
{

	/* LINGO */

	/* initialize variables */
	Lingo lingo = { .wordSize = 5 };
	
	/* SERVER */
	
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
		lingo.connfd = connfd;
		
		switch(checkRequestType((char *)recvline))
		{
			case GET:
			{
				//printRequestFirstLine((char *)recvline); printf("\n"); fflush(stdout);
				getPage((char *)recvline, message);
				getLingoVariable((char *)recvline, &lingo, message);
				break;
			}
			case POST:
			{
				printParams((char *)recvline); fflush(stdout);
				if((get_key_and_value((char *)recvline, &param) < 0))
				{
					printf("Invalid { key : value } pair!\n");
				}	
				lingo_input(&lingo, &param);
				buildLingoPage(&lingo, message);
				break;
			}
			default:
			{
				err_n_die("Package type error.");
				break;
			}
		}
		
		snprintf( (char *)buff, sizeof(buff), "HTTP/1.0 200 OK\r\n\r\n%s", message);
		write_socket(connfd, (char *)buff);
		close(connfd);
	}
	free(message);
	
	return 0;
}