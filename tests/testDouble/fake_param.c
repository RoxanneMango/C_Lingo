#include "fake_param.h"

bool
is_letter(char letter)
{
	return ( ( (tolower(letter) < LOWER_LETTER_A) || (tolower(letter) > LOWER_LETTER_Z) ) ? false : true );
}

bool
is_number(char letter)
{
	return ( ( (letter < STR_ZERO) || (letter > STR_NINE) ) ? false : true );
}

bool
isValid(char * word, int size)
{
	for(int i = 0; i < size; ++i)
	{
		if(!is_letter(word[i]) && (word[i] != UNDER_SCORE) && !is_number(word[i]))
		{
			return false;
		}
	}
	return true;
}