#ifndef PAGE_REQUESTS_H
#define PAGE_REQUESTS_H

#include "lingo.h"

#define POST 0
#define GET 1
#define PUT 2
#define PATCH 3
#define DELETE 4

void printRequest(char * request);
void printRequestFirstLine(char * request);
int checkRequestType(char * request);
void getPage(char * request, char * message);

#endif // PAGE_REQUESTS