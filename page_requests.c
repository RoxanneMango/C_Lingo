#include <string.h>
#include "page_requests.h"
#include "file_io.h"

void
printRequest(char * request)
{
	for(int i = 0; i < strlen(request); i++)
	{
		printf("%c", request[i]);
	}
	printf("\n\n\n");
}

void
printRequestFirstLine(char * request)
{
	for(int i = 0; request[i] != 'H'; i++)
	{
		printf("%c", request[i]);
	}
}

int 
checkRequestType(char * request)
{
	int type;
	if(strncmp(request, "POST", 4) == 0)
	{
		type = POST;
	}
	else if(strncmp(request, "GET", 3) == 0)
	{
		type = GET;
	}
	else if(strncmp(request, "PUT", 3) == 0)
	{
		type = PUT;
	}
	else if(strncmp(request, "PATCH", 5) == 0)
	{
		type = PATCH;
	}
	else if(strncmp(request, "DELETE", 6) == 0)
	{
		type = DELETE;
	}
	else
	{
		type = -1;
	}
	return type;
}

void
getPage(char * request, char * message)
{
	if(strncmp(request, "GET / ", 6) == 0)
	{
		getFileContent("index.html", message);
	}
	if(strncmp(request, "GET /favicon.ico", 16) == 0)
	{
		//strcpy(message, "HTTP/1.0 200 OK\r\n\r\n");
		//getFileContent("img/icon.ico", message);
		//strcpy(header, "Content-Type: text/css");
	}
	else if(strncmp(request, "GET /manual.html", 16) == 0)
	{
		getFileContent("manual.html", message);
	}
	else if(strncmp(request, "GET /lingo_setup.html", 21) == 0)
	{
		getFileContent("lingo_setup.html", message);
	}
	else if(strncmp(request, "GET /lingo.html ", 15) == 0)
	{
		getFileContent("lingo.html", message);
	}
	else if(strncmp(request, "GET /about.html", 15) == 0)
	{
		getFileContent("about.html", message);
	}
	else if(strncmp(request, "GET /index.html", 15) == 0)
	{
		getFileContent("index.html", message);
	}
	else if(strncmp(request, "GET /style.css", 14) == 0)
	{
		//strcpy(header, "Content-Type: text/css");
		getFileContent("style.css", message);
	}
}