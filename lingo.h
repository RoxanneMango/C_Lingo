#ifndef LINGO_H
#define LINGO_H

#include "param.h"
#include "high_scores.h"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include <pthread.h>

/* * * * * * * * * * * * * * * * * 
* Game commands:				 *
*- - - - - - - - - - - - - - - - *
* { "<key>" : "<value>" }		 *
*- - - - - - - - - - - - - - - - *
* lingo_game : start			 *
* lingo_game : quit				 *
*- - - - - - - - - - - - - - - - *
* lingo_guess : <word>			 *
*- - - - - - - - - - - - - - - - *
* lingo_size : <word_size>		 *
*								 *
* * * * * * * * * * * * * * * * */

#define GUESS_TIME 15
#define NAME_TIME 60

#define FIVE_LETTER_WORD_FILE "lingoWords/five_letter_words.txt"
#define SIX_LETTER_WORD_FILE "lingoWords/six_letter_words.txt"
#define SEVEN_LETTER_WORD_FILE "lingoWords/seven_letter_words.txt"

typedef struct Lingo
{
	/* Array indexes and bounds */
	int index;
	int hintSize;
	int wordSize;
	int numberOfGuesses;
	int guessesRemaining;

	/* Lingo game stats */
	char * word;
	char * hints;
	char ** guesses;
	//
	int score;
	char * name;
	
	/* flags */
	bool guessed;
	bool isRunning;
	bool isLost;
	bool isWon;
	bool isWonAck;
	bool killSignal;
	
	/* Time */
	time_t startTime;
	time_t endTime;
	int guessTime;
	int lostCountDown;
	
	/* threads */
	pthread_t thread;
	bool mutex_free;
	
} Lingo;

void * lingo_game(void * void_lingo);

void lingo_start(struct Lingo * lingo);
void lingo_stop(struct Lingo * lingo);

void lingo_input(struct Lingo * lingo, Param * param);
void getLingoVariable(char * request, struct Lingo * lingo, char * message);
void getRandomWord(char * word, int size, char * file_name);

bool letterIsPresent(unsigned int dictionary[][2], int wordSize, char letter);
void buildLetterFlags(char * guess, char * word, int wordSize, char * message);
void buildLingoPage(struct Lingo * lingo, char * message);

#endif // LINGO_H