#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

void err_n_die(const char * fmt, ...);

#endif // ERROR_HANDLING_H