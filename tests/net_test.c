#include "net_test.h"

bool
net_test()
{
	int number_of_tests = 12;
	int passed_tests = 0;

	printf("\033[1;30m-- Starting networking test suite --\n\n");

	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in servaddr;

	memset(&servaddr, 0, sizeof(struct sockaddr_in));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(LOCALHOST);
	servaddr.sin_port = htons(SERVER_PORT+1);
	
	printf("\033[1;30m- LOCALHOST:\n");
	
	// INIT_SOCKET_LOCALHOST
	printf("\033[1;30m> initializing socket:\t %s\n", socket_test(&listenfd) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	// SIN_FAMILY_LOCALHOST
	printf("\033[1;30m> setting sin_family:\t %s\n", sin_family_test(servaddr, AF_INET) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	// SIN_IP_LOCALHOST
	printf("\033[1;30m> setting sin_addr:\t %s\n", sin_addr_test(servaddr, LOCALHOST) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	// SIN_PORT_LOCALHOST
	printf("\033[1;30m> setting sin_port:\t %s\n", sin_port_test(servaddr, SERVER_PORT+1) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	// BIND_SOCKET_LOCALHOST
	printf("\033[1;30m> binding socket:\t %s\n", bind_test(&listenfd, servaddr) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	// LISTEN_SOCKET_LOCALHOST
	printf("\033[1;30m> listen on socket:\t %s\n", listen_test(&listenfd) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");	
	
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	
	memset(&servaddr, 0, sizeof(struct sockaddr_in));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	servaddr.sin_port = htons(SERVER_PORT);
	
	printf("\n\033[1;30m- PUBLIC:\n");

	// INIT_SOCKET
	printf("\033[1;30m> initializing socket:\t %s\n", socket_test(&listenfd) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	// SIN_FAMILY
	printf("\033[1;30m> setting sin_family:\t %s\n", sin_family_test(servaddr, AF_INET) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	// SIN_IP
	printf("\033[1;30m> setting sin_addr:\t %s\n", sin_addr_test(servaddr, SERVER_IP) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	// SIN_PORT
	printf("\033[1;30m> setting sin_port:\t %s\n", sin_port_test(servaddr, SERVER_PORT) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	// BIND_SOCKET	
	printf("\033[1;30m> binding socket:\t %s\n", bind_test(&listenfd, servaddr) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	// LISTEN_SOCKET
	printf("\033[1;30m> listen on socket:\t %s\n", listen_test(&listenfd) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");

	// NUM_OF_PASSED_TESTS
	printf("\033[1;30m\nNumber of passed tests:\t %s%d/%d\033[1;30m\n", (passed_tests == number_of_tests ? "\033[1;32m" : "\033[1;31m"), passed_tests, number_of_tests);
	
	return (passed_tests == number_of_tests);
}

bool
socket_test(int * listenfd)
{
	return (TEST_IS_GREATER_THAN(*listenfd, 0));
}

bool
sin_family_test(struct sockaddr_in servaddr, int type)
{
	return (TEST_IS_EQUAL(servaddr.sin_family, type));
}

bool
sin_addr_test(struct sockaddr_in servaddr, char * ip_address)
{
	return (TEST_IS_EQUAL(servaddr.sin_addr.s_addr, inet_addr(ip_address)));
}

bool
sin_port_test(struct sockaddr_in servaddr, int server_port)
{
	return (TEST_IS_EQUAL(servaddr.sin_port, htons(server_port)));
}

bool
bind_test(int * listenfd, struct sockaddr_in servaddr)
{	
	return (TEST_IS_ZERO(bind(*listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr))));
}

bool
listen_test(int * listenfd)
{
	return (TEST_IS_ZERO(listen(*listenfd, 10)));
}

/*
bool
connect_test()
{
	socklen_t addr_len;
	if( (*connfd = accept(*listenfd, (struct sockaddr *) &addr, &addr_len ) ) < 0 )
	{
		err_n_die("Connection error.");
	}
}
*/