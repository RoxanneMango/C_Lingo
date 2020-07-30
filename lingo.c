#include "lingo.h"

bool
letterExists(char guess, char * word, int wordSize, bool * possibleLetters)
{
	for(int i = 0; i < wordSize; ++i)
	{
		if(guess == word[i])
		{
			if(possibleLetters[i])
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
	bool * possibleLetters = calloc(wordSize, sizeof(bool));
	char letter[1];
			
	for(int j = 0; j < wordSize; ++j)
	{
		letter[0] = guess[j];
		if(guess[j] == word[j])
		{
			strcat(message, "=");
		}
		else if(letterExists(guess[j], word, wordSize, possibleLetters))
		{
			strcat(message, "?");
		}
		else
		{
			strcat(message, "!");
		}
		strcat(message, letter);
		strcat(message, ";");
	}
	
	free(possibleLetters);
}


void
buildLingoPage(struct Lingo * lingo, char * message)
{
	if(!lingo->isRunning)
	{
		for(int i = 0; i < lingo->wordSize; ++i)
		{
			strcat(message, "(;");
			for(int j = 0; j < lingo->wordSize; ++j)
			{
				strcat(message, "_;");
			}
			strcat(message, ");");
		}
	}
	else
	{
		printf("wordSize : %d ; guessesRemaining : %d\n", lingo->wordSize, lingo->guessesRemaining);

		for(int i = 0; i < (lingo->wordSize - (lingo->guessesRemaining)); ++i)
		{
			strcat(message, "(;");
			//for(int j = 0; j < lingo->wordSize; ++j)
			//{
				buildLetterFlags(lingo->guesses[i], lingo->word, lingo->wordSize, message);
			//}
			strcat(message, ");");
		}
		char letter[1];		
		if(lingo->guessesRemaining)
		{
			strcat(message, "(;");
			for(int i = 0; i < lingo->wordSize; ++i)
			{
				letter[0] = lingo->hints[i];
				strcat(message, letter);
				strcat(message, ";");
			}
			strcat(message, ");");
		}
		for(int i = (lingo->wordSize - (lingo->guessesRemaining)+1); i < lingo->wordSize; i++)
		{
			strcat(message, "(;");
			for(int j = 0; j < lingo->wordSize; ++j)
			{
				strcat(message, "_;");
			}
			strcat(message, ");");
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
	lingo->guessesRemaining = lingo->wordSize;
	lingo->word = calloc(lingo->wordSize, sizeof(char));
	getRandomWord(lingo->word, lingo->wordSize);
	
	lingo->hintSize = 1;
	lingo->hints = calloc(lingo->wordSize, sizeof(char));
	
	printf("Random word: %s\n", lingo->word);
	
	/* Allocating the guesses */
	lingo->guesses = (char **) calloc(lingo->wordSize, sizeof(char *));
	for(int i = 0; i < lingo->wordSize; ++i)
	{
		lingo->guesses[i] = (char *) calloc(lingo->wordSize, sizeof(char *));
		lingo->hints[i] = '.';
	}
	
	for(int i = 0; i < lingo->hintSize; i++)
	{
		lingo->hints[i] = lingo->word[i];
	}
	
	lingo->guessTime = 59;	

	lingo->isWon = false;

	lingo->isRunning = true;
	lingo->guessesRemaining = lingo->wordSize;
	lingo->startTime = time(0);
	lingo->endTime = lingo->startTime + lingo->guessTime;
	
	lingo->index = 0;
	
	pthread_create(&lingo->thread, NULL, lingo_game, (void *)lingo);
}

void *
lingo_game(void * void_lingo)
{	
	struct Lingo * lingo = void_lingo;
	for(;;)
	{
		if(!lingo->isRunning)
		{
			lingo_stop(lingo);
			return NULL;
		}
		
		lingo->index = lingo->wordSize - lingo->guessesRemaining;
		lingo->index = lingo->index >= lingo->wordSize ? lingo->index-1 : lingo->index;
		
		if(strcmp(lingo->word, lingo->guesses[lingo->index]) == 0)
		{
			printf("YOU WON!\n");
			lingo->isWon = true;
			lingo->isRunning = false;
		}

		if(lingo->guessed)
		{
			lingo->guessed = false;
			lingo->guessesRemaining -= 1;
			lingo->startTime = time(0);
			lingo->endTime = lingo->startTime + lingo->guessTime;
		}

		if(!lingo->guessesRemaining)
		{
			lingo->isRunning = false;
		}

		if(time(0) >= lingo->endTime)
		{
			lingo->startTime = time(0);
			lingo->endTime = lingo->startTime + lingo->guessTime;
			lingo->guessesRemaining -= 1;
			sleep(1);
		}
		lingo->mutex_free = true;
		sleep(1);
	}
}

void
lingo_stop(struct Lingo * lingo)
{
	lingo->isRunning = false;
	for(int i = 0; i < lingo->wordSize; ++i)
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
			printf("START GAME\n");
			if(!lingo->isRunning)
			{
				lingo_start(lingo);
			}
		}
		else if(!strcmp(param->value, "quit"))
		{
			if(lingo->isRunning)
			{
				lingo->isRunning = false;
				printf("QUIT\n");
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
		if(lingo->isRunning)
		{
			if(isValid(param->value, lingo->wordSize))
			{
				for(int j = 0; j < lingo->wordSize; ++j)
				{
					lingo->guesses[lingo->wordSize - lingo->guessesRemaining][j] = param->value[j];
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
		if(lingo->isRunning)
		{
			strcpy(message, "true");
		}
		else
		{
			strcpy(message, "false");
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