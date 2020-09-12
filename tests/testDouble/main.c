#include "lingo_test.h"

int
main(int argc, char ** argv)
{	
	int number_of_suites = 8;
	int passed_suites = 0;
	
	// Create Lingo struct instance
	Lingo lingo = { .wordSize = 5 };
	// Create Param struct instance
	Param param =
	{
		.key = calloc(15, sizeof(char)),
		.value = calloc(15, sizeof(char))
	};
	
	printf("\033[1;30m-- Starting fake lingo test suite --\n\n");
	//
	lingo_start_test(&lingo, &param) ? ++passed_suites : 0;
	lingo_stop_test(&lingo, &param) ? ++passed_suites : 0;
	lingo_game_rotation_test(&lingo) ? ++passed_suites : 0;
	//
	lingo_isWon_ack_test(&lingo, &param) ? ++passed_suites : 0;
	//
	lingo_invalid_guess_test(&lingo, &param) ? ++passed_suites : 0;
	lingo_wrong_guess_test(&lingo, &param) ? ++passed_suites : 0;
	lingo_correct_guess_test(&lingo, &param) ? ++passed_suites : 0;
	//
	lingo_time_test(&lingo) ? ++passed_suites : 0;
	// Free param resources
	free(param.key);
	free(param.value);
	
	// NUM_OF_PASSED_TESTS
	printf("\033[1;30m\nNumber of passed suites: %s%d/%d\n\033[0m", (passed_suites == number_of_suites ? "\033[1;32m" : "\033[1;31m"), passed_suites, number_of_suites);
	
	return (passed_suites == number_of_suites ? 0 : 1);
}