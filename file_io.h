#ifndef FILE_IO_H
#define FILE_IO_H

#include "error_handling.h"

int getFileSize(char * fileName);
void getFileContent(char * fileName, char * message);

#endif // FILE_IO_H