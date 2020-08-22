#ifndef SERVER_H
#define SERVER_H

#include <arpa/inet.h>
#include "page_requests.h"
#include "param.h"
#include "file_io.h"
#include "lingo.h"

#define SERVER_IP "192.168.1.9"
#define LOCALHOST "127.0.0.1"
#define SERVER_PORT 44900

#define MAXLINE 8192

void * server(void * void_lingo);

void create_socket(int * listenfd, struct sockaddr_in servaddr, char * ip_address, int server_port);
void connect_client(int * connfd, int * listenfd, struct sockaddr_in addr, uint8_t * recvline, char * client_address);

void write_socket(int connfd, char * buffer);

#endif // SERVER_H