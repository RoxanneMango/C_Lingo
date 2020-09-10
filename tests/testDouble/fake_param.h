#ifndef FAKE_PARAM_H
#define FAKE_PARAM_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define LOWER_LETTER_A 97
#define LOWER_LETTER_Z 122

#define STR_ZERO 48
#define STR_NINE 57

#define UNDER_SCORE 95

typedef struct
Param
{
	char * key;
	char * value;
} Param;

bool is_letter(char letter);
bool is_number(char letter);
bool isValid(char * word, int size);

#endif // FAKE_PARAM_H