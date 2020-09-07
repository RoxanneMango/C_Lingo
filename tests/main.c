#include "net_test.h"

int
main(int argc, char ** argv)
{
	net_test();
	printf("assert result: %d\n", TEST_IS_EQUAL(1,2));
}