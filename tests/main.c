#include "net_test.h"
#include "file_test.h"
#include "mem_test.h"

int
main(int argc, char ** argv)
{
	bool is_remote = false;
	if(argc > 1)
	{
		if(!strcmp(argv[1], "--local"))
		{
			is_remote = true;
		}
	}
	
	int number_of_suites = 3;
	int suites_passed = 0;

	printf("\033[48;2;0;0;0m");

	net_test(is_remote) ? ++suites_passed : 0;
	printf("\n");
	file_test() ? ++suites_passed : 0;
	printf("\n");
	mem_test() ? ++suites_passed : 0;
	printf("\n");
	printf("\033[1;30m--\nNumber of passed suites: %s%d/%d\033[1;30m\n--\n\033[0m", (suites_passed == number_of_suites ? "\033[1;32m" : "\033[1;31m"), suites_passed, number_of_suites);

	printf("\033[0");

	return ((suites_passed == number_of_suites) ? 0 : 1);
}
