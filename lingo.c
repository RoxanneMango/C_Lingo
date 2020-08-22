#include "lingo.h"

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

	printf("Answer: %s\n", *answer); fflush(stdout);
	
	strcat(message, "(");
	strcat(message, *answer);
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

/*
void
buildLetter(char * letter, char * message)
{	
	strcat(message, "<li><div class=\"letter\">");
	strcat(message, (char *)letter);
	strcat(message, "</div></li>");
}

void
buildBlankWord(int wordSize, char * message)
{
	strcat(message,"<ul>");
	for(int i = 0; i < wordSize; ++i)
	{
		strcat(message,"<li><div class=\"letter\" style=\"color:rgba(0,0,0,0.0);\">.</div></li>");
	}
	strcat(message, "</ul>");	
}

void
buildWord(char * word, int wordSize, char * message)
{
	char letter[1] = "";
	strcat(message,"<ul>");
	for(int i = 0; i < wordSize; ++i)
	{
		letter[0] = *(word+i);
		buildLetter(letter, message);
	}
	strcat(message, "</ul>");
}
*/

void
getRandomWord(char * word, int size)
{
	switch(size)
	{
		case 5:
		{
			strcpy(word, "hello");
			break;
		}
		case 6:
		{
			strcpy(word, "police");
			break;
		}
		case 7:
		{
			strcpy(word, "website");
			break;
		}
	}
}

void
lingo_start(struct Lingo * lingo)
{
	lingo->index = 0;
	lingo->numberOfGuesses = 5;
	lingo->guessesRemaining = lingo->numberOfGuesses;
	
	lingo->word = calloc(lingo->wordSize, sizeof(char));
	getRandomWord(lingo->word, lingo->wordSize);
	
	lingo->hintSize = 1;
	lingo->hints = calloc(lingo->wordSize, sizeof(char));
	
	printf("Random word: %s\n", lingo->word);
	
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
	lingo->isRunning = true;
	lingo->killSignal = false;
	
	lingo->guessTime = 15;	
	lingo->startTime = time(0);
	lingo->endTime = lingo->startTime + lingo->guessTime;
	
	pthread_create(&lingo->thread, NULL, lingo_game, (void *)lingo);
}

void *
lingo_game(void * void_lingo)
{	
	struct Lingo * lingo = void_lingo;
	printf("STARTING LINGO . . .\n");
	for(;;)
	{
		//char buff[100] = {0};
		//snprintf(buff, sizeof(buff), "HTTP/1.0 200 OK\r\n\r\ntesttest");
		//snprintf(buff, sizeof(buff), "testtest");
		//write_socket(lingo->connfd, buff);
		
		if(strcmp(lingo->word, lingo->guesses[lingo->index]) == 0)
		{
			lingo->isWon = true;
			lingo->killSignal = true;
		}

		if(lingo->guessed)
		{
			lingo->guessed = false;
			lingo->guessesRemaining -= 1;
			lingo->index += 1;
			lingo->startTime = time(0);
			lingo->endTime = lingo->startTime + lingo->guessTime;
		}

		if(!lingo->guessesRemaining)
		{
			lingo->killSignal = true;
		}

		if(time(0) >= lingo->endTime)
		{
			lingo->killSignal = true;
		}
		lingo->mutex_free = true;
		if(lingo->killSignal)
		{
			printf("DEALLOCATING IN 3 SECONDS . . .\n");
			sleep(3);
			lingo_stop(lingo);
		}
		if(!lingo->isRunning)
		{
			return NULL;
		}	
		sleep(1);
	}
}

void
lingo_stop(struct Lingo * lingo)
{
	lingo->isRunning = false;
	for(int i = 0; i < lingo->numberOfGuesses; ++i)
	{
		free(lingo->guesses[i]);
	}
	free(lingo->guesses);
	printf("EXITING LINGO . . .\n");
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
	
	if(!strcmp(param->key, "lingo_size"))
	{
		if(!lingo->isRunning)
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
		if(lingo->isRunning && !lingo->killSignal)
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
				lingo->mutex_free = false;
				lingo->guessed = true;
				while(!lingo->mutex_free)
				{
					sleep(0.2);
				}
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
		sprintf(message, "%ld", (lingo->isRunning ? lingo->endTime - time(0) : 0));
	}
	else if(strncmp(request, "GET /lingo_size", 15) == 0)
	{
		sprintf(message, "%d", (lingo->isRunning ? lingo->wordSize : 0));
	}
}