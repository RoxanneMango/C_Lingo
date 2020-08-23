#include <stdio.h>

#include "lingo_words.h"

int
main(int argc, char ** argv)
{
	if(argc == 1)
	{
		printf("Give input file.\n");
		return 0;
	}
	
	printf("Looking through input file `%s` . . .\n", argv[argc-1]);
	find_words(*(argv+argc-1));	
	printf("Done. Input written to:\n%s;\n%s;\n%s;\n", FIVE_LETTERS, SIX_LETTERS, SEVEN_LETTERS);
	
	return 0;
}