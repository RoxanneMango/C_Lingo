#include "param.h"

int
getParamSize(char * request)
{
	int count = 0;
	for(int i = strlen(request); request[i] != '\n'; i--)
	{
		count += 1;
	}
	return count;
}

void
printParams(char * recvline)
{
	for(int i = (strlen(recvline) - getParamSize(recvline)); i < strlen(recvline); i++)
	{	
		if(recvline[i] == '=')
		{
			printf(" = ");
		}
		else if(recvline[i] == '&')
		{
			printf("\n");
		}
		else
		{
			printf("%c", recvline[i]);
		}
	}
	printf("\n");
}

bool
is_letter(char letter)
{
	return ( ( (tolower(letter) < LOWER_LETTER_A) || (tolower(letter) > LOWER_LETTER_Z) ) ? false : true );
}

bool
isValid(char * word, int size)
{
	for(int i = 0; i < size; ++i)
	{
		if(!is_letter(word[i]))
		{
			return false;
		}
	}
	return true;
}

int
get_key_and_value(char * recvline, Param * param)
{
	memset(param->key, 0, 15);
	memset(param->value, 0, 15);
	
	bool isKey = false;
	bool isValue = false;

	int key_i = 0;
	int value_i = 0;

	int count = getParamSize(recvline);

	for(int i = (strlen(recvline) - count); i < strlen(recvline); i++)
	{
		if(isKey)
		{
			if(recvline[i] == '\"')
			{
				isKey = false;
				continue;
			}
			param->key[key_i] = tolower(recvline[i]);
			key_i += 1;
		}
		else if(isValue)
		{
			if(recvline[i] == '\"')
			{
				isValue = false;
				break;
			}
			
			if(!is_letter(recvline[i]))
			{
				memset(param->value, 0, 15);
				return -1;
			}
			
			param->value[value_i] = tolower(recvline[i]);
			value_i += 1;
		}
		if(recvline[i] == '\"' && !isValue)
		{
			isKey = true;
		}
		if(recvline[i] == ':')
		{
			isValue = true;
			i += 1;
		}
	}
	return 0;
}