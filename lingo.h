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

typedef struct Lingo
{
	char * word;
	int wordSize;
	int numberOfGuesses;
	int guessesRemaining;
	bool isRunning;
	
	bool isLost;
	int lostCountDown;
	
	char * name;
	int score;
	bool isWon;
	bool killSignal;
	
	char ** guesses;
	int index;
	bool guessed;
	
	int hintSize;
	char * hints;
	
	time_t startTime;
	time_t endTime;
	int guessTime;
	
	pthread_t thread;
	bool mutex_free;
	
	bool isWonAck;
	
} Lingo;

void * lingo_game(void * void_lingo);

void lingo_start(struct Lingo * lingo);
void lingo_stop(struct Lingo * lingo);

void lingo_input(struct Lingo * lingo, Param * param);
void getLingoVariable(char * request, struct Lingo * lingo, char * message);
void getRandomWord(char * word, int size);

bool letterIsPresent(unsigned int dictionary[][2], int wordSize, char letter);
void buildLetterFlags(char * guess, char * word, int wordSize, char * message);
void buildLingoPage(struct Lingo * lingo, char * message);

#endif // LINGO_H


/* * * * * * * * * * * * * * * * * * * * * * * * 
* 
* A. Player chooses how many lettered word to guess
* 0. Lingo chooses random word from word list
* a. Game starts, timer starts counting down. Both client and server sided.
* 1. Get send word by client
* 2. Sanitize string to retrieve word
* 3. pass word to word builder
* 4. wordBuilder passes word to letterBuilder, letter by letter.
* 5. wordBuilder returns formatted HTML code to be inserted into the lingo_word div
* 6. if timer runs out before guess is made, turn is skipped.
* 7. if guess is made, timer resets.
* 
* 
* 
* 
* * * * * * * * * * * * * * * * * * * * * * * */