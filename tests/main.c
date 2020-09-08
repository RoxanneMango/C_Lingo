#include "net_test.h"
#include "file_test.h"
#include "mem_test.h"

int
main(int argc, char ** argv)
{
	int number_of_suites = 3;
	int suites_passed = 0;
	
	net_test() ? ++suites_passed : 0;
	printf("\n");
	file_test() ? ++suites_passed : 0;
	printf("\n");
	mem_test() ? ++suites_passed : 0;
	printf("\n");
	printf("\033[1;30m--\nNumber of passed suites: %s%d/%d\033[1;30m\n--\n\033[0m", (suites_passed == number_of_suites ? "\033[1;32m" : "\033[1;31m"), suites_passed, number_of_suites);

	return ((suites_passed == number_of_suites) ? 0 : 1);
}
