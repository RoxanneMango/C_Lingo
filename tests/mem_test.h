#ifndef MEM_TEST_H
#define MEM_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "tests.h"
#include "../server.h"

bool mem_test();

bool static_code_analysis_test();
bool calloc_test(char * buffer);
bool realloc_test(char * buffer);

#endif // MEM_TEST_H