#include "net_test.h"

extern int errno;

bool
net_test()
{
	int number_of_tests = 11;
	int passed_tests = 0;

/*	
	printf("\033[1;30m-- Starting networking test suite --\n\n");

	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	
	// INIT_SOCKET
	printf("\033[1;30m> initializing socket:\t\t %s\n\n", socket_test(listenfd) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");

	struct sockaddr_in servaddr;

	memset(&servaddr, 0, sizeof(struct sockaddr_in));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(LOCALHOST);
	servaddr.sin_port = htons(SERVER_PORT+1);
	
	// SIN_FAMILY
	printf("\033[1;30m> setting sin_family LOCALHOST:\t %s\n", TEST_IS_EQUAL(servaddr.sin_family, AF_INET) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	// SIN_IP_LOCALHOST
	printf("\033[1;30m> setting sin_addr LOCALHOST:\t %s\n", TEST_IS_EQUAL(servaddr.sin_addr.s_addr, inet_addr(LOCALHOST)) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	// SIN_PORT_LOCALHOST
	printf("\033[1;30m> setting sin_port LOCALHOST:\t %s\n", TEST_IS_EQUAL(servaddr.sin_port, htons(SERVER_PORT+1)) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	// BIND_SOCKET_LOCALHOST
	printf("\033[1;30m> binding socket LOCALHOST:\t %s\n", TEST_IS_ZERO(bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr))) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	// LISTEN_SOCKET_LOCALHOST
	printf("\033[1;30m> listen on socket LOCALHOST:\t %s\n", TEST_IS_ZERO(listen(listenfd, 10)) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");	
	
	memset(&servaddr, 0, sizeof(struct sockaddr_in));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
	servaddr.sin_port = htons(SERVER_PORT);
	
	// SIN_FAMILY
	printf("\n\033[1;30m> setting sin_family:\t\t %s\n", TEST_IS_EQUAL(servaddr.sin_family, AF_INET) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	// SIN_IP
	printf("\033[1;30m> setting sin_addr:\t\t %s\n", TEST_IS_EQUAL(servaddr.sin_addr.s_addr, inet_addr("0.0.0.0")) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	// SIN_PORT
	printf("\033[1;30m> setting sin_port:\t\t %s\n", TEST_IS_EQUAL(servaddr.sin_port, htons(SERVER_PORT)) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	// BIND_SOCKET	
	printf("\033[1;30m> binding socket:\t\t %s\n", TEST_IS_ZERO(bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr))) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	// LISTEN_SOCKET
	printf("\033[1;30m> listen on socket:\t\t %s\n", TEST_IS_ZERO(listen(listenfd, 10)) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");

	// NUM_OF_PASSED_TESTS
	printf("\033[1;30m\nNumber of passed tests: %d/%d\n", passed_tests, number_of_tests);
*/
	
	int listenfd;
	struct sockaddr_in servaddr;
	
	if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		printf("Error: %s\n", strerror(errno));
	}
	else
	{
		printf("SOCKET:\t\tPASSED\n");
	}
	memset(&servaddr, 0, sizeof(struct sockaddr_in));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	servaddr.sin_port = htons(SERVER_PORT);
	
	if( (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr))) < 0 )
	{
		servaddr.sin_addr.s_addr = inet_addr(LOCALHOST);
		servaddr.sin_port = htons(SERVER_PORT+1);
		
		if( (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr))) < 0 )
		{
			printf("Error: %s\n", strerror(errno));
		}
		else
		{
			printf("LC_BIND:\t\tPASSED\n");
		}
	}
	else
	{
		printf("BIND:\t\tPASSED\n");
	}
	
	if( (listen(listenfd, 10)) < 0 )
	{
		printf("Error: %s\n", strerror(errno));
	}
	else
	{
		printf("LISTEN:\t\tPASSED\n");
	}
	
	return true;
}

bool
socket_test(int * listenfd)
{
	*listenfd = socket(AF_INET, SOCK_STREAM, 0);
	return (TEST_IS_GREATER_THAN(listenfd, 0));
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