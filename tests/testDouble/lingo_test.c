#include "lingo_test.h"

bool
lingo_start_test(struct Lingo * lingo, Param * param)
{
	int number_of_tests = 16;
	int passed_tests = 0;
	//
	char * word_5 = "lingo";
	//
	strcpy(param->key, "lingo_game");
	strcpy(param->value, "start");
	
	// lingo initial values check
	printf("\033[1;30m\n- lingo start check:\n");
	//
	lingo_input(lingo, param);
	//
	printf("\033[1;30m> checking value isRunning:\t\t %s\n", TEST_IS_EQUAL(lingo->isRunning, true) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value isLost:\t\t %s\n", TEST_IS_ZERO(lingo->isLost) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value killSignal:\t\t %s\n", TEST_IS_ZERO(lingo->killSignal) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value isWon:\t\t\t %s\n", TEST_IS_ZERO(lingo->isWon) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	//
	printf("\033[1;30m> checking value score:\t\t\t %s\n", TEST_IS_ZERO(lingo->score) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value index:\t\t\t %s\n", TEST_IS_ZERO(lingo->index) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value numberOfGuesses:\t %s\n", TEST_IS_EQUAL(lingo->numberOfGuesses, 5) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value guessesRemaining:\t %s\n", TEST_IS_EQUAL(lingo->guessesRemaining, 5) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value wordSize:\t\t %s\n", TEST_IS_EQUAL(lingo->wordSize, 5) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value hintSize:\t\t %s\n", TEST_IS_EQUAL(lingo->hintSize, 1) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	//
	printf("\033[1;30m> checking value word:\t\t\t %s\n", TEST_IS_ZERO(strcmp(lingo->word, word_5)) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value hints:\t\t\t %s\n", TEST_IS_EQUAL(lingo->hints[0], word_5[0]) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	//
	printf("\033[1;30m> checking value guessTime:\t\t %s\n", TEST_IS_EQUAL(lingo->guessTime, GUESS_TIME) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value startTime:\t\t %s\n", TEST_IS_EQUAL(lingo->startTime, 0) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value currentTime:\t\t %s\n", TEST_IS_EQUAL(lingo->currentTime, 0) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value endTime:\t\t %s\n", TEST_IS_EQUAL(lingo->endTime, GUESS_TIME) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	
	// NUM_OF_PASSED_TESTS
	printf("\033[1;30m\nNumber of passed tests:\t %s%d/%d\n\033[0m", (passed_tests == number_of_tests ? "\033[1;32m" : "\033[1;31m"), passed_tests, number_of_tests);
	
	return (passed_tests == number_of_tests);
}

bool
lingo_stop_test(struct Lingo * lingo, Param * param)
{
	int number_of_tests = 1;
	int passed_tests = 0;

	strcpy(param->key, "lingo_game");
	strcpy(param->value, "quit");
	// lingo stop check
	printf("\033[1;30m\n- lingo stop check:\n");
	//
	lingo_input(lingo, param);
	lingo_game(lingo);
	//
	printf("\033[1;30m> checking value isRunning:\t\t %s\n", TEST_IS_ZERO(lingo->isRunning) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");	

	// NUM_OF_PASSED_TESTS
	printf("\033[1;30m\nNumber of passed tests:\t %s%d/%d\n\033[0m", (passed_tests == number_of_tests ? "\033[1;32m" : "\033[1;31m"), passed_tests, number_of_tests);

	return (passed_tests == number_of_tests);
}

bool
lingo_game_rotation_test(struct Lingo * lingo)
{
	char * word_5 = "lingo";
	char * word_6 = "police";
	char * word_7 = "website";

	int number_of_tests = 12;
	int passed_tests = 0;

	// lingo game rotation check
	printf("\033[1;30m\n- lingo game rotation check:\n");
	//
	lingo_start(lingo);
	printf("\033[1;30m> checking value wordSize (5):\t\t %s\n", TEST_IS_EQUAL(lingo->wordSize, 5) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value word (5):\t\t %s\n", TEST_IS_ZERO(strcmp(lingo->word, word_5)) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value hints (5):\t\t %s\n", TEST_IS_EQUAL(lingo->hints[0], word_5[0]) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	//
	lingo_restart(lingo);
	printf("\033[1;30m> checking value wordSize (6):\t\t %s\n", TEST_IS_EQUAL(lingo->wordSize, 6) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value word (6):\t\t %s\n", TEST_IS_ZERO(strcmp(lingo->word, word_6)) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value hints (6):\t\t %s\n", TEST_IS_EQUAL(lingo->hints[0], word_6[0]) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	//
	lingo_restart(lingo);
	printf("\033[1;30m> checking value wordSize (7):\t\t %s\n", TEST_IS_EQUAL(lingo->wordSize, 7) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value word (7):\t\t %s\n", TEST_IS_ZERO(strcmp(lingo->word, word_7)) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value hints (7):\t\t %s\n", TEST_IS_EQUAL(lingo->hints[0], word_7[0]) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	//
	lingo_restart(lingo);
	printf("\033[1;30m> checking value wordSize (5):\t\t %s\n", TEST_IS_EQUAL(lingo->wordSize, 5) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value word (5):\t\t %s\n", TEST_IS_ZERO(strcmp(lingo->word, word_5)) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value hints (5):\t\t %s\n", TEST_IS_EQUAL(lingo->hints[0], word_5[0]) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	//
	lingo_stop(lingo);
	
	// NUM_OF_PASSED_TESTS
	printf("\033[1;30m\nNumber of passed tests:\t %s%d/%d\n\033[0m", (passed_tests == number_of_tests ? "\033[1;32m" : "\033[1;31m"), passed_tests, number_of_tests);

	return (passed_tests == number_of_tests);
}

bool
lingo_isWon_ack_test(struct Lingo * lingo, Param * param)
{
	int number_of_tests = 3;
	int passed_tests = 0;

	strcpy(param->key, "lingo_is_won_ack");
	strcpy(param->value, "ack");

	// lingo game rotation check
	printf("\033[1;30m\n- lingo isWon_ack check:\n");
	//
	lingo_start(lingo);
	lingo->isWon = true;
	//
	printf("\033[1;30m> checking value isWon:\t\t\t %s\n", TEST_IS_EQUAL(lingo->isWon, true) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value isWonAck:\t\t %s\n", TEST_IS_ZERO(lingo->isWonAck) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	//
	lingo_input(lingo, param);
	//
	printf("\033[1;30m> checking value isWonAck:\t\t %s\n", TEST_IS_EQUAL(lingo->isWonAck, true) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	//
	lingo_stop(lingo);
	
	// NUM_OF_PASSED_TESTS
	printf("\033[1;30m\nNumber of passed tests:\t %s%d/%d\n\033[0m", (passed_tests == number_of_tests ? "\033[1;32m" : "\033[1;31m"), passed_tests, number_of_tests);

	return (passed_tests == number_of_tests);
}

bool
lingo_invalid_guess_test(struct Lingo * lingo, Param * param)
{
	int number_of_tests = 2;
	int passed_tests = 0;

	strcpy(param->key, "lingo_guess");
	strcpy(param->value, "ling0");

	// lingo game rotation check
	printf("\033[1;30m\n- lingo invalid guess check:\n");
	//
	lingo_start(lingo);
	//
	printf("\033[1;30m> checking value guessed:\t\t %s\n", TEST_IS_ZERO(lingo->guessed) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	lingo_input(lingo, param);
	printf("\033[1;30m> checking value guessed:\t\t %s\n", TEST_IS_ZERO(lingo->guessed) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	//
	lingo_stop(lingo);
	
	// NUM_OF_PASSED_TESTS
	printf("\033[1;30m\nNumber of passed tests:\t %s%d/%d\n\033[0m", (passed_tests == number_of_tests ? "\033[1;32m" : "\033[1;31m"), passed_tests, number_of_tests);

	return (passed_tests == number_of_tests);
}

bool
lingo_wrong_guess_test(struct Lingo * lingo, Param * param)
{
	int number_of_tests = 5;
	int passed_tests = 0;

	strcpy(param->key, "lingo_guess");
	strcpy(param->value, "local");

	// lingo game rotation check
	printf("\033[1;30m\n- lingo wrong guess check:\n");
	//
	lingo_start(lingo);
	lingo_input(lingo, param);
	//
	printf("\033[1;30m> checking value guessesRemaining:\t %s\n", TEST_IS_EQUAL(lingo->guessesRemaining, 5) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value guessed:\t\t %s\n", TEST_IS_EQUAL(lingo->guessed, true) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	lingo_game(lingo);
	printf("\033[1;30m> checking value guessesRemaining:\t %s\n", TEST_IS_EQUAL(lingo->guessesRemaining, 4) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value guessed:\t\t %s\n", TEST_IS_ZERO(lingo->guessed) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	//
	char output[32] = {0};
	char * answer = "(=l?o!c!a!l)";
	buildLetterFlags(param->value, lingo->word, lingo->wordSize, output);
	printf("\033[1;30m> checking value guess[0]:\t\t %s\n", TEST_IS_ZERO(strcmp(output, answer)) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	//
	lingo_stop(lingo);
	
	// NUM_OF_PASSED_TESTS
	printf("\033[1;30m\nNumber of passed tests:\t %s%d/%d\n\033[0m", (passed_tests == number_of_tests ? "\033[1;32m" : "\033[1;31m"), passed_tests, number_of_tests);

	return (passed_tests == number_of_tests);
}

bool
lingo_correct_guess_test(struct Lingo * lingo, Param * param)
{
	int number_of_tests = 8;
	int passed_tests = 0;

	strcpy(param->key, "lingo_guess");
	strcpy(param->value, "lingo");

	// lingo game rotation check
	printf("\033[1;30m\n- lingo correct guess check:\n");
	//
	lingo_start(lingo);
	lingo_input(lingo, param);
	//
	printf("\033[1;30m> checking value score:\t\t\t %s\n", TEST_IS_ZERO(lingo->score) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value guessesRemaining:\t %s\n", TEST_IS_EQUAL(lingo->guessesRemaining, 5) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value guessed:\t\t %s\n", TEST_IS_EQUAL(lingo->guessed, true) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	lingo_game(lingo);
	printf("\033[1;30m> checking value isWon:\t\t\t %s\n", TEST_IS_EQUAL(lingo->isWon, true) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");	
	printf("\033[1;30m> checking value score:\t\t\t %s\n", TEST_IS_EQUAL(lingo->score, 50) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");	
	char output[32] = {0};
	char * answer = "(=l=i=n=g=o)";
	buildLetterFlags(param->value, lingo->word, lingo->wordSize, output);
	printf("\033[1;30m> checking value guess[0]:\t\t %s\n", TEST_IS_ZERO(strcmp(output, answer)) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	lingo->isWonAck = true;
	lingo_game(lingo);
	printf("\033[1;30m> checking value guessesRemaining:\t %s\n", TEST_IS_EQUAL(lingo->guessesRemaining, 5) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	printf("\033[1;30m> checking value wordSize:\t\t %s\n", TEST_IS_EQUAL(lingo->wordSize, 6) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	//
	lingo_stop(lingo);
	
	// NUM_OF_PASSED_TESTS
	printf("\033[1;30m\nNumber of passed tests:\t %s%d/%d\n\033[0m", (passed_tests == number_of_tests ? "\033[1;32m" : "\033[1;31m"), passed_tests, number_of_tests);

	return (passed_tests == number_of_tests);
}

bool
lingo_time_test(struct Lingo * lingo)
{
	int number_of_tests = 2;
	int passed_tests = 0;

	// lingo game rotation check
	printf("\033[1;30m\n- lingo time check:\n");
	//
	lingo_start(lingo);
	lingo_game(lingo);
	//
	printf("\033[1;30m> checking value isLost:\t\t %s\n", TEST_IS_ZERO(lingo->isLost) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	lingo->currentTime = GUESS_TIME + 1;
	lingo_game(lingo);
	printf("\033[1;30m> checking value isLost:\t\t %s\n", TEST_IS_EQUAL(lingo->isLost, 1) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	//
	lingo_stop(lingo);
	
	// NUM_OF_PASSED_TESTS
	printf("\033[1;30m\nNumber of passed tests:\t %s%d/%d\n\033[0m", (passed_tests == number_of_tests ? "\033[1;32m" : "\033[1;31m"), passed_tests, number_of_tests);

	return (passed_tests == number_of_tests);
}