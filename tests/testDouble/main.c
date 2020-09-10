#include "fake_lingo.h"
#include "../tests.h"

int
main()
{
	int number_of_tests = 29;
	int passed_tests = 0;	
	
	char * word_5 = "lingo";
	char * word_6 = "police";
	char * word_7 = "website";
	
	// Create Lingo struct instance
	Lingo lingo = { .wordSize = 5 };
	
	// Create Param struct instance
	Param param =
	{
		.key = calloc(15, sizeof(char)),
		.value = calloc(15, sizeof(char))
	};
	
	printf("\033[1;30m-- Starting fake lingo test --\n\n");
	
	// lingo initial values check
	printf("\033[1;30m- lingo start check:\n");
	//
	strcpy(param.key, "lingo_game");
	strcpy(param.value, "start");
	lingo_input(&lingo, &param);
	printf("\033[1;30m> checking value isRunning:\t\t %s\n", TEST_IS_EQUAL(lingo.isRunning, true) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value isLost:\t\t %s\n", TEST_IS_ZERO(lingo.isLost) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value killSignal:\t\t %s\n", TEST_IS_ZERO(lingo.killSignal) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value isWon:\t\t\t %s\n", TEST_IS_ZERO(lingo.isWon) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	//
	printf("\033[1;30m> checking value score:\t\t\t %s\n", TEST_IS_ZERO(lingo.score) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value index:\t\t\t %s\n", TEST_IS_ZERO(lingo.index) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value numberOfGuesses:\t %s\n", TEST_IS_EQUAL(lingo.numberOfGuesses, 5) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value guessesRemaining:\t %s\n", TEST_IS_EQUAL(lingo.guessesRemaining, 5) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value wordSize:\t\t %s\n", TEST_IS_EQUAL(lingo.wordSize, 5) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value hintSize:\t\t %s\n", TEST_IS_EQUAL(lingo.hintSize, 1) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	//
	printf("\033[1;30m> checking value word:\t\t\t %s\n", TEST_IS_ZERO(strcmp(lingo.word, word_5)) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value hints:\t\t\t %s\n", TEST_IS_EQUAL(lingo.hints[0], word_5[0]) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	//
	printf("\033[1;30m> checking value guessTime:\t\t %s\n", TEST_IS_EQUAL(lingo.guessTime, GUESS_TIME) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value startTime:\t\t %s\n", TEST_IS_EQUAL(lingo.startTime, 0) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value currentTime:\t\t %s\n", TEST_IS_EQUAL(lingo.currentTime, 0) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value endTime:\t\t %s\n", TEST_IS_EQUAL(lingo.endTime, GUESS_TIME) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	
	// lingo stop check
	printf("\033[1;30m\n- lingo stop check:\n");
	//
	strcpy(param.value, "quit");
	lingo_input(&lingo, &param);
	lingo_game(&lingo);
	printf("\033[1;30m> checking value isRunning:\t\t %s\n", TEST_IS_ZERO(lingo.isRunning) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");	
	
	// lingo game rotation check
	printf("\033[1;30m\n- lingo game rotation check:\n");
	//
	lingo_start(&lingo);
	printf("\033[1;30m> checking value wordSize (5):\t\t %s\n", TEST_IS_EQUAL(lingo.wordSize, 5) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value word (5):\t\t %s\n", TEST_IS_ZERO(strcmp(lingo.word, word_5)) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value hints (5):\t\t %s\n", TEST_IS_EQUAL(lingo.hints[0], word_5[0]) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	//
	lingo_restart(&lingo);
	printf("\033[1;30m> checking value wordSize (6):\t\t %s\n", TEST_IS_EQUAL(lingo.wordSize, 6) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value word (6):\t\t %s\n", TEST_IS_ZERO(strcmp(lingo.word, word_6)) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value hints (6):\t\t %s\n", TEST_IS_EQUAL(lingo.hints[0], word_6[0]) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	//
	lingo_restart(&lingo);
	printf("\033[1;30m> checking value wordSize (7):\t\t %s\n", TEST_IS_EQUAL(lingo.wordSize, 7) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value word (7):\t\t %s\n", TEST_IS_ZERO(strcmp(lingo.word, word_7)) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value hints (7):\t\t %s\n", TEST_IS_EQUAL(lingo.hints[0], word_7[0]) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	//
	lingo_restart(&lingo);
	printf("\033[1;30m> checking value wordSize (5):\t\t %s\n", TEST_IS_EQUAL(lingo.wordSize, 5) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value word (5):\t\t %s\n", TEST_IS_ZERO(strcmp(lingo.word, word_5)) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value hints (5):\t\t %s\n", TEST_IS_EQUAL(lingo.hints[0], word_5[0]) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	//
	lingo_stop(&lingo);

	// lingo

	// Free param resources
	free(param.key);
	free(param.value);
	
	// NUM_OF_PASSED_TESTS
	printf("\033[1;30m\nNumber of passed tests:\t %s%d/%d\n\033[0m", (passed_tests == number_of_tests ? "\033[1;32m" : "\033[1;31m"), passed_tests, number_of_tests);
	
	return 0;
	//return (passed_tests == number_of_tests);
}