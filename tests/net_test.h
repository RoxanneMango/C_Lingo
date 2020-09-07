#ifndef NET_TEST_H
#define NET_TEST_H

#include "tests.h"
#include "../server.h"
#include "../lingo.h"

bool net_test();

bool socket_test(int * listenfd);
bool bind_test(int * listenfd, struct sockaddr_in servaddr);
bool listen_test(int * listenfd);

bool sin_family_test(struct sockaddr_in servaddr, int type);
bool sin_addr_test(struct sockaddr_in servaddr, char * ip_address);
bool sin_port_test(struct sockaddr_in servaddr, int server_port);

#endif // NET_TEST_H