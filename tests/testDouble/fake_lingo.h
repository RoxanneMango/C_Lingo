#ifndef FAKE_LINGO_H
#define FAKE_LINGO_H

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "fake_param.h"

#define GUESS_TIME 15
#define NAME_TIME 60

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
	time_t currentTime;
	time_t endTime;
	int guessTime;
	int lostCountDown;
	
} Lingo;

void lingo_game(struct Lingo * lingo);

void lingo_start(struct Lingo * lingo);
void lingo_restart(struct Lingo * lingo);
void lingo_stop(struct Lingo * lingo);

void lingo_input(struct Lingo * lingo, Param * param);
void getLingoVariable(char * request, struct Lingo * lingo, char * message);

bool letterIsPresent(unsigned int dictionary[][2], int wordSize, char letter);
void buildLetterFlags(char * guess, char * word, int wordSize, char * message);
void buildLingoPage(struct Lingo * lingo, char * message);

#endif // FAKE_LINGO_H