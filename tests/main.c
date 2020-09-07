#include "net_test.h"
#include "file_test.h"

int
main(int argc, char ** argv)
{
	int number_of_suites = 2;
	int suites_passed = 0;
	
	net_test() ? ++suites_passed : 0;
	printf("\n");
	file_test() ? ++suites_passed : 0;
	
	return ((suites_passed == number_of_suites) ? 0 : 1);
}
