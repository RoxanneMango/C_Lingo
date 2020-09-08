#include "mem_test.h"

bool mem_test()
{
	int number_of_tests = 3;
	int passed_tests = 0;
	
	char * buffer = NULL;
	
	printf("\033[1;30m-- Starting memory test suite --\n\n");
	
	// calloc
	printf("\033[1;30m> allocating memory with calloc():\t\t %s\n", calloc_test(buffer) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	// realloc
	printf("\033[1;30m> reallocating memory with realloc():\t\t %s\n", realloc_test(buffer) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	// free (does not return anything ; cannot be evaluated)
	free(buffer);	
	
	// static code analysis
	printf("\033[1;30m> equal number of calloc() and free():\t\t %s\n", static_code_analysis_test() ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");

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

bool
static_code_analysis_test()
{	

	// Get all *.c files
	
	DIR * DIR_P;
	struct dirent * dir;
	char files[32][64] = {0};
	
	if((DIR_P = opendir("../")) == 0)
	{
		printf("Could not open directory . . .\n");
		exit(1);
	}
	int i = 0;
	while((dir = readdir(DIR_P)) != NULL)
	{
		if(dir->d_name[strlen(dir->d_name)-1] == 'c')
		{
			sprintf(files[i], "%s", dir->d_name);
			++i;
		}
	}
	closedir(DIR_P);

	// zero initialize variables
	char PATH[64] = {0};
	FILE * FP = NULL;
	
	char c = 0;
	char * buffer = NULL;
	char * buffer_Ptr = NULL;

	int buffer_size = 0;
	int num_of_alloc = 0;
	int num_of_free = 0;

	char * free_str_spc = " free(";
	char * free_str_scn = ";free(";
	char * free_str_nln = "\nfree(";
	char * free_str_tab = "\tfree(";
	//
	char * calloc_str_spc = " calloc(";
	char * calloc_str_scn = ";calloc(";
	char * calloc_str_nln = "\ncalloc(";
	char * calloc_str_tab = "\tcalloc(";
	
	// Count all occurances of calloc() and free()
	for(int i = 0; strlen(files[i]); ++i)
	{
		// Create file PATH
		memset(PATH, 0, 64);
		sprintf(PATH, "../%s", files[i]);

		// count number of characters in files[i]
		FP = fopen(PATH, "r");
		while ((c = fgetc(FP)) != EOF)
		{
			buffer_size += 1;;
		}
		fclose(FP);
		
		// allocate resources for buffer and point buffer_Ptr to its first element
		buffer = (char *) calloc(buffer_size, sizeof(char));
		buffer_Ptr = buffer;
		
		// Populate buffer with contents of files[i] and rewind buffer_Ptr
		FP = fopen(PATH, "r");
		while ((c = fgetc(FP)) != EOF)
		{
			*buffer_Ptr = c;
			buffer_Ptr++;
		}
		buffer_Ptr = buffer;
		fclose(FP);

		// Find occurances of free();
		while ( (buffer_Ptr = strstr(buffer_Ptr, free_str_spc)) != NULL ) {
			buffer_Ptr += strlen(free_str_spc); num_of_free++;
			//printf("in file: %s\n", files[i]);
		}
		buffer_Ptr = buffer;
		while ( (buffer_Ptr = strstr(buffer_Ptr, free_str_scn)) != NULL ) {
			buffer_Ptr += strlen(free_str_scn); num_of_free++;
			//printf("in file: %s\n", files[i]);
		}
		buffer_Ptr = buffer;		
		while ( (buffer_Ptr = strstr(buffer_Ptr, free_str_nln)) != NULL ) {
			buffer_Ptr += strlen(free_str_nln); num_of_free++;
			//printf("in file: %s\n", files[i]);
		}
		buffer_Ptr = buffer;				
		while ( (buffer_Ptr = strstr(buffer_Ptr, free_str_tab)) != NULL ) {
			buffer_Ptr += strlen(free_str_tab); num_of_free++;
			//printf("in file: %s\n", files[i]);
		}
		buffer_Ptr = buffer;
		
		// Find occurances of calloc();
		while ( (buffer_Ptr = strstr(buffer_Ptr, calloc_str_spc)) != NULL ) {
			buffer_Ptr += strlen(calloc_str_spc); num_of_alloc++;
			//printf("in file: %s\n", files[i]);
		}
		buffer_Ptr = buffer;
		while ( (buffer_Ptr = strstr(buffer_Ptr, calloc_str_scn)) != NULL ) {
			buffer_Ptr += strlen(calloc_str_scn); num_of_alloc++;
			//printf("in file: %s\n", files[i]);
		}
		buffer_Ptr = buffer;		
		while ( (buffer_Ptr = strstr(buffer_Ptr, calloc_str_nln)) != NULL ) {
			buffer_Ptr += strlen(calloc_str_nln); num_of_alloc++;
			//printf("in file: %s\n", files[i]);
		}
		buffer_Ptr = buffer;				
		while ( (buffer_Ptr = strstr(buffer_Ptr, calloc_str_tab)) != NULL ) {
			buffer_Ptr += strlen(calloc_str_tab); num_of_alloc++;
			//printf("in file: %s\n", files[i]);
		}
		free(buffer);
	}

//	printf("number of allocations: %d\n", num_of_alloc);
//	printf("number of frees: %d\n", num_of_free);

	return (num_of_alloc == num_of_free);
}