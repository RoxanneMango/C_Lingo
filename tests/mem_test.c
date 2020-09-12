#include "mem_test.h"

bool mem_test()
{
	int number_of_tests = 2;
	int passed_tests = 0;
	
	char * buffer = NULL;
	
	printf("\033[1;30m-- Starting memory test suite --\n\n");
	
	// calloc
	printf("\033[1;30m> allocating memory with calloc():\t\t %s\n", calloc_test(buffer) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	// realloc
	printf("\033[1;30m> reallocating memory with realloc():\t\t %s\n", realloc_test(buffer) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	// free (does not return anything ; cannot be evaluated)
	free(buffer);	

	// NUM_OF_PASSED_TESTS
	printf("\033[1;30m\nNumber of passed tests:\t %s%d/%d\n\033[0m", (passed_tests == number_of_tests ? "\033[1;32m" : "\033[1;31m"), passed_tests, number_of_tests);
	
	return (passed_tests == number_of_tests);
}

bool
calloc_test(char * buffer)
{
	buffer = (char *) calloc(MAXLINE, sizeof(char));
	return (buffer != NULL);
}

bool
realloc_test(char * buffer)
{
	buffer = (char *) realloc(buffer, MAXLINE * sizeof(char));
	return (buffer != NULL);
}