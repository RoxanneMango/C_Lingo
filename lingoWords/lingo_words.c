#include "lingo_words.h"

bool
is_letter(char letter)
{
	return ( ( (tolower(letter) < LOWER_LETTER_A) || (tolower(letter) > LOWER_LETTER_Z) ) ? false : true );
}

void
find_words(char * file_in)
{
	// Clean files
	FILE * FP_5 = fopen(FIVE_LETTERS, "w");
	FILE * FP_6 = fopen(SIX_LETTERS, "w");
	FILE * FP_7 = fopen(SEVEN_LETTERS, "w");
	fclose(FP_5);
	fclose(FP_6);
	fclose(FP_7);
	// Open in append mode //
	FP_5 = fopen(FIVE_LETTERS, "a");
	FP_6 = fopen(SIX_LETTERS, "a");
	FP_7 = fopen(SEVEN_LETTERS, "a");

	// Open file to search through in read mode //
	FILE * FP = fopen(file_in, "r");

	char word[7] = {0};
	int wordSize = 0;

	int i = 0;
	char c[1] = {0};
	while ((c[0] = fgetc(FP)) != EOF)
	{
		if(is_letter(c[0]))
		{
			wordSize += 1;
			if(wordSize > 7)
			{
			  continue;
			}
			else
			{
				strncat(word, c, 1);
			}
		}
		else
		{
			if(wordSize == 5)
			{
			  fprintf(FP_5, "%s;", word);
			}
			else if(wordSize == 6)
			{
			  fprintf(FP_6, "%s;", word);
			}
			else if(wordSize == 7)
			{
			  fprintf(FP_7, "%s;", word);
			}
			wordSize = 0;
			memset(word, 0, 7);
		}
		i += 1;
	}
	if (feof(FP))
	{
		fclose(FP);
		fclose(FP_5);
		fclose(FP_6);
		fclose(FP_7);
		return;
	}
}