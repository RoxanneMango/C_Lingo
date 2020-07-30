#include "file_io.h"

int 
getFileSize(char * fileName)
{
	FILE * FP = fopen(fileName, "r");
	int i = 0;
	int c;
	
	while ((c = fgetc(FP)) != EOF)
	{
	  i++;
	}
	if (feof(FP))
	{
		fclose(FP);
		return i;
	}
	err_n_die("File error");
	return -1;
}

void
getFileContent(char * fileName, char * message)
{	
	FILE * FP = fopen(fileName, "r");
	
	int i = 0;
	char c;
	while ((c = fgetc(FP)) != EOF)
	{
	  *(message + i) = c;
	  i += 1;
	}
	if (feof(FP))
	{
		fclose(FP);
		return;
	}
}