#include "file_test.h"

// LINGO_WORDS_FILE_PATH_MACROS
	// FIVE_LETTERS
	// SIX_LETTERS
	// SEVEN_LETTERS

// C_LINGO_FILE_PATH_MACROS
	// FIVE_LETTER_WORD_FILE
	// SIX_LETTER_WORD_FILE
	// SEVEN_LETTER_WORD_FILE
	// HIGH_SCORE

bool
file_test()
{
	char PATH[MAX_PATH_SIZE] = {0};
	int number_of_tests = 7;
	int passed_tests = 0;
	
	printf("\033[1;30m-- Starting file test suite --\n\n");
	
	// lingo_words
	printf("\033[1;30m- lingo_words:\n");
	
	// FIVE_LETTERS
	snprintf(PATH, MAX_PATH_SIZE, "../lingoWords/%s", FIVE_LETTERS);
	printf("\033[1;30m> opening %s:\t %s\n", PATH, file_open_test(PATH) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	memset(PATH, 0, MAX_PATH_SIZE);
	// SIX_LETTERS
	snprintf(PATH, MAX_PATH_SIZE, "../lingoWords/%s", SIX_LETTERS);
	printf("\033[1;30m> opening %s:\t %s\n", PATH, file_open_test(PATH) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	memset(PATH, 0, MAX_PATH_SIZE);
	// SEVEN_LETTERS
	snprintf(PATH, MAX_PATH_SIZE, "../lingoWords/%s", SEVEN_LETTERS);
	printf("\033[1;30m> opening %s:\t %s\n", PATH, file_open_test(PATH) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	memset(PATH, 0, MAX_PATH_SIZE);
	
	// C_Lingo
	printf("\n\033[1;30m- c_lingo:\n");
	
	// FIVE_LETTER_WORD_FILE
	snprintf(PATH, MAX_PATH_SIZE, "../%s", FIVE_LETTER_WORD_FILE);
	printf("\033[1;30m> opening %s:\t %s\n", PATH, file_open_test(PATH) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	memset(PATH, 0, MAX_PATH_SIZE);
	// SIX_LETTER_WORD_FILE
	snprintf(PATH, MAX_PATH_SIZE, "../%s", SIX_LETTER_WORD_FILE);
	printf("\033[1;30m> opening %s:\t %s\n", PATH, file_open_test(PATH) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	memset(PATH, 0, MAX_PATH_SIZE);
	// SEVEN_LETTER_WORD_FILE
	snprintf(PATH, MAX_PATH_SIZE, "../%s", SEVEN_LETTER_WORD_FILE);
	printf("\033[1;30m> opening %s:\t %s\n", PATH, file_open_test(PATH) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	memset(PATH, 0, MAX_PATH_SIZE);
	// HIGH_SCORE
	snprintf(PATH, MAX_PATH_SIZE, "../%s", HIGH_SCORE);
	printf("\033[1;30m> opening %s:\t\t\t %s\n", PATH, file_open_test(PATH) ? ++passed_tests, "\033[1;32mSUCCESSFUL" : "\033[1;31mFAILED");
	memset(PATH, 0, MAX_PATH_SIZE);
	
	// NUM_OF_PASSED_TESTS
	printf("\033[1;30m\nNumber of passed tests:\t %s%d/%d\n\033[0m", (passed_tests == number_of_tests ? "\033[1;32m" : "\033[1;31m"), passed_tests, number_of_tests);
	
	return (passed_tests == number_of_tests);
}

bool
file_open_test(char * PATH)
{
	return (fopen(PATH, "r") != 0 ? true : false);
}