#ifndef TESTS_H
#define TESTS_H

#include <assert.h>
#include <stdbool.h>

#define TEST_IS_ZERO(x) (x == 0)
#define TEST_IS_EQUAL(x,y) (x == y)
#define TEST_IS_NOT_EQUAL(x,y) (x != y)
#define TEST_IS_GREATER_THAN(x,y) (x > y)
#define TEST_IS_LESSER_THAN(x,y) (x < y)

#include "../server.h"
#include "../lingo.h"

#endif // TEST_H
