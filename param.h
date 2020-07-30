#ifndef PARAM_H
#define PARAM_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define LOWER_LETTER_A 97
#define LOWER_LETTER_Z 122

typedef struct
Param
{
	char * key;
	char * value;
} Param;

int getParamSize(char * request);
void printParams(char * request);
bool is_letter(char letter);
bool isValid(char * word, int size);
int get_key_and_value(char * recvline, Param * param);

#endif // PARAM_H