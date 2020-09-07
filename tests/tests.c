#include "tests.h"

bool
mem_test()
{
	// Memory is initialized properly (calloc == zero)
	// Memory is free'd properly (count allocations vs free -> analyze source code. --> static analyzser, though
	return true;
}

bool
type_test()
{
	return true;
}

bool
file_test()
{
	// MAXSIZE is bigger than largest file size to be send.
	// All file paths are valid
	// 
	return true;
}