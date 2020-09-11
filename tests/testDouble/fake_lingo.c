#include "fake_lingo.h"

void
lingo_start(struct Lingo * lingo)
{	
//	printf("STARTING LINGO . . .\n");
	lingo->isLost = false;
	lingo->lostCountDown = NAME_TIME;
	lingo->name = (char *) calloc(16, sizeof(char));
	for(int i = 0; i < 16; ++i)
	{
		lingo->name[i] = '.';
	}
	
	lingo->score = 0;
	
	lingo->index = 0;
	lingo->numberOfGuesses = 5;
	lingo->guessesRemaining = lingo->numberOfGuesses;
	
	lingo->wordSize = 5;
	
	lingo->word = (char *) calloc(lingo->wordSize, sizeof(char));
	strcpy(lingo->word, "lingo");

	lingo->hintSize = 1;
	lingo->hints = (char *) calloc(lingo->wordSize, sizeof(char));
	
	/* Allocating the guesses */
	lingo->guesses = (char **) calloc(lingo->numberOfGuesses, sizeof(char *));
	for(int i = 0; i < lingo->numberOfGuesses; ++i)
	{
		lingo->guesses[i] = (char *) calloc(lingo->wordSize, sizeof(char *));
	}
	for(int i = 0; i < lingo->wordSize; ++i)
	{
		lingo->hints[i] = '.';
	}
	
	for(int i = 0; i < lingo->hintSize; i++)
	{
		lingo->hints[i] = lingo->word[i];
	}
	
	lingo->isWon = false;
	lingo->isWonAck = false;
	lingo->isRunning = true;
	lingo->killSignal = false;
	
	lingo->guessTime = GUESS_TIME;
	lingo->startTime = 0;
	lingo->currentTime = 0;
	lingo->endTime = lingo->startTime + lingo->guessTime;
}

void
lingo_restart(struct Lingo * lingo)
{
//	printf("RESTARTING LINGO . . .\n");
	
	lingo->index = 0;
	lingo->guessesRemaining = lingo->numberOfGuesses;
	
	if(lingo->wordSize == 5)
	{
		lingo->wordSize = 6;
	}
	else if(lingo->wordSize == 6)
	{
		lingo->wordSize = 7;
	}
	else if(lingo->wordSize == 7)
	{
		lingo->wordSize = 5;
	}
	
	lingo->word = (char *) realloc(lingo->word, lingo->wordSize * sizeof(char));

	switch(lingo->wordSize)
	{
		case 5:
		{
			strcpy(lingo->word, "lingo");
			break;
		}
		case 6:
		{
			strcpy(lingo->word, "police");
			break;
		}
		case 7:
		{
			strcpy(lingo->word, "website");
			break;
		}
	}
	
	lingo->hintSize = 1;
	lingo->hints = (char *) realloc(lingo->hints, lingo->wordSize * sizeof(char));
	
	for(int i = 0; i < lingo->numberOfGuesses; ++i)
	{
		lingo->guesses[i] = (char *) realloc(lingo->guesses[i], lingo->wordSize * sizeof(char *));
	}
	for(int i = 0; i < lingo->wordSize; ++i)
	{
		lingo->hints[i] = '.';
	}
	
	for(int i = 0; i < lingo->hintSize; i++)
	{
		lingo->hints[i] = lingo->word[i];
	}
		
	lingo->startTime = 0;
	lingo->currentTime = 0;
	lingo->endTime = lingo->startTime + lingo->guessTime;
		
	lingo->isWon = false;
	lingo->isWonAck = false;
}

void
lingo_game(struct Lingo * lingo)
{	
//	printf("RUNNING LINGO . . .\n");
	// Clamp index value so it doesn't go out of range //
	if(lingo->index > lingo->numberOfGuesses-1)
	{
		lingo->index = lingo->numberOfGuesses-1;
	}
	// String lacks null termination character, hence why strncmp instead of strcmp //
	if(strncmp(lingo->word, lingo->guesses[lingo->index], lingo->wordSize) == 0)
	{
		lingo->isWon = true;
		lingo->score += (10 * lingo->guessesRemaining);
	}
	if(lingo->guessed)
	{
		if(lingo->guesses[lingo->index][0] != lingo->word[0])
		{
			lingo->isLost = true;
		}
		lingo->guessed = false;
		lingo->guessesRemaining -= 1;
		lingo->index += 1;
		lingo->startTime = lingo->currentTime;
		lingo->endTime = lingo->startTime + lingo->guessTime;
	}
	if((!lingo->guessesRemaining) || (lingo->currentTime >= lingo->endTime))
	{
		lingo->isLost = true;
	}
	
	if(lingo->isLost)
	{
		if(!lingo->lostCountDown)
		{
			lingo->killSignal = true;
		}
	}
	if(lingo->isWonAck)
	{
		lingo_restart(lingo);
	}	
	if(lingo->killSignal)
	{
		lingo_stop(lingo);
	}
}

void
lingo_stop(struct Lingo * lingo)
{	
	for(int i = 0; i < lingo->numberOfGuesses; ++i)
	{
		free(lingo->guesses[i]);
	}
	free(lingo->guesses);
	free(lingo->name);
	free(lingo->word);
	free(lingo->hints);
	
	lingo->isRunning = false;
//	printf("EXITING LINGO . . .\n");
}

void
lingo_input(struct Lingo * lingo, Param * param)
{
	if(!strcmp(param->key, "lingo_game"))
	{
		if(!strcmp(param->value, "start"))
		{
			if(!lingo->isRunning)
			{
				lingo_start(lingo);
			}
		}
		else if(!strcmp(param->value, "quit"))
		{
			if(lingo->isRunning && !lingo->killSignal)
			{
				lingo->killSignal = true;
			}
		}
	}
	if(!strcmp(param->key, "lingo_add_name"))
	{
		if(lingo->isRunning && !lingo->killSignal && lingo->isLost)
		{
			if(!strcmp(param->value, ""))
			{
				return;
			}
			strncpy(lingo->name, param->value, 14);
			lingo->killSignal = true;
		}
	}
	if(!strcmp(param->key, "lingo_is_won_ack"))
	{
		if(lingo->isRunning && lingo->isWon)
		{
			if(!strcmp(param->value, "ack"))
			{
				lingo->isWonAck = true;
			}
		}
	}
	
	if(!strcmp(param->key, "lingo_size"))
	{
		if(lingo->isRunning)
		{
			if(!strcmp(param->value, "five"))
			{
				lingo->wordSize = 5;
			}
			else if(!strcmp(param->value, "six"))
			{
				lingo->wordSize = 6;
			}
			else if(!strcmp(param->value, "seven"))
			{
				lingo->wordSize = 7;
			}
		}
	}
	if(!strcmp(param->key, "lingo_guess"))
	{
		if(lingo->isRunning && !lingo->killSignal && !lingo->isLost)
		{
			if(isValid(param->value, lingo->wordSize))
			{
				for(int j = 0; j < lingo->wordSize; ++j)
				{
					lingo->guesses[lingo->index][j] = param->value[j];
					if(param->value[j] == lingo->word[j])
					{
						lingo->hints[j] = param->value[j];
					}
				}
				lingo->guessed = true;
			}
		}
	}
}

void 
getLingoVariable(char * request, struct Lingo * lingo, char * message)
{
	if(strncmp(request, "GET /lingo_board", 16) == 0)
	{
		buildLingoPage(lingo, message);
	}
	else if(strncmp(request, "GET /lingo_is_running", 21) == 0)
	{
		if(lingo->isRunning && !lingo->killSignal)
		{
			strcpy(message, "1");
		}
		else
		{
			strcpy(message, "0");
		}
	}
	else if(strncmp(request, "GET /lingo_is_lost", 18) == 0)
	{
		if(lingo->isLost)
		{
			strcpy(message, "1");
		}
		else
		{
			strcpy(message, "0");
		}
	}
	else if(strncmp(request, "GET /lingo_score", 16) == 0)
	{
		sprintf(message, "%d", lingo->score);
	}
	else if(strncmp(request, "GET /lingo_high_scores", 22) == 0)
	{
		strcpy(message, "high_score");
	}
	else if(strncmp(request, "GET /lingo_is_won", 17) == 0)
	{
		if(lingo->isWon)
		{
			strcpy(message, "1");
		}
		else
		{
			strcpy(message, "0");
		}
	}
	else if(strncmp(request, "GET /lingo_guesses_remaining", 28) == 0)
	{
		sprintf(message, "%d", (lingo->isRunning ? lingo->guessesRemaining : 0 ));
	}
	else if(strncmp(request, "GET /lingo_time_remaining", 25) == 0)
	{
		sprintf(message, "%ld", (lingo->isRunning ? lingo->endTime - lingo->currentTime : 0));
	}
	else if(strncmp(request, "GET /lingo_size", 15) == 0)
	{
		sprintf(message, "%d", (lingo->isRunning ? lingo->wordSize : 0));
	}
}

bool
letterIsPresent(unsigned int dictionary[][2], int wordSize, char letter)
{
	for(int i = 0; i < wordSize; ++i)
	{
		if(dictionary[i][0] == letter)
		{
			if(dictionary[i][1] > 0)
			{
				return true;
			}
		}
	}
	return false;
}

void
buildLetterFlags(char * guess, char * word, int wordSize, char * message)
{	
	// init //
	char answer[wordSize][2];
	for(int i = 0; i < wordSize; ++i)
	{
		answer[i][0] = '!';answer[i][1] = guess[i];
	}
	unsigned int dictionary[wordSize][2];
	for(int i = 0; i < wordSize; ++i)
	{
		dictionary[i][0] = '_';dictionary[i][1] = 0;
	}
	
	// Populate //
	for(int i = 0, x = 0; i < wordSize; ++i)
	{
		if(letterIsPresent(dictionary, wordSize, guess[i]))
		{
			continue;
		}
		for(int j = 0; j < wordSize; ++j)
		{
			if(guess[i] == word[j])
			{
				dictionary[x][0] = guess[i];
				dictionary[x][1] += 1;
			}
		}
		x += 1;
	}
	
	// Check guess with dictionary and if found, remove entry
	for(int i = 0; i < wordSize; ++i)
	{
		if(guess[i] == word[i])
		{
			answer[i][0] = '=';
			
			// Remove dictionary entry
			for(int j = 0; j < wordSize; ++j)
			{
				if(guess[i] == dictionary[j][0])
				{
					dictionary[j][1] -= 1;
					break;
				}
			}
		}
	}

	for(int i = 0; i < wordSize; ++i)
	{
		if(letterIsPresent(dictionary, wordSize, guess[i]))
		{
			if(!(guess[i] == word[i]))
			{
				answer[i][0] = '?';
				// Remove dictionary entry
				for(int j = 0; j < wordSize; ++j)
				{
					if(guess[i] == dictionary[j][0])
					{
						dictionary[j][1] -= 1;
						break;
					}
				}	
			}
		}
	}
	strcat(message, "(");
	strncat(message, *answer, (wordSize*2));	// Keep in account a lack of null termination characters //
	strcat(message, ")");
}

void
buildLingoPage(struct Lingo * lingo, char * message)
{
	if(!lingo->isRunning)
	{
		for(int i = 0; i < lingo->numberOfGuesses; ++i)
		{
			strcat(message, "(");
			for(int j = 0; j < lingo->wordSize; ++j)
			{
				strcat(message, "_");
			}
		}
	}
	else
	{
		for(int i = 0; i < lingo->index; ++i)
		{
			strcat(message, "(");
			buildLetterFlags(lingo->guesses[i], lingo->word, lingo->wordSize, message);
			strcat(message, ")");
		}
		char letter[1];		
		if(lingo->guessesRemaining && !lingo->isWon)
		{
			strcat(message, "(");
			for(int i = 0; i < lingo->wordSize; ++i)
			{
				strcat(message, "!");
				letter[0] = lingo->hints[i];
				strcat(message, letter);
			}
			strcat(message, ")");
		}
		for(int i = lingo->index; i < lingo->numberOfGuesses-1 + (lingo->isWon); i++)
		{
			strcat(message, "(");
			for(int j = 0; j < lingo->wordSize; ++j)
			{
				strcat(message, "_");
			}
			strcat(message, ")");
		}
	}
}