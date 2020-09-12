#include "high_scores.h"

void
add_score(char * fileName, char * name, int score)
{
	// check if file_size doesn't exceed 256 characters (16*16) //
	if(getFileSize(fileName) > 256)
	{
		return;
	}
	// Ain't nobody got time for that //
	if(!score)
	{
		return;
	}
	// cap score //
	if(score > 99999999)
	{
		score = 99999999;
	}
	
	// declare and initialize default variables //
	FILE * FP;
	char array[512] = {0};
//	memset(array, 0, 512);
	
	char names[10][14] = {0};
	
	for(int i = 0; i < 10; ++i)
	{
		for(int j = 0; j < 14; ++j)
		{
			names[i][j] = '.';
		}
	}
	int scores[10] = {0};
	
	// put contents in scores array //
	getFileContent(fileName, array);
	
	// sanitize score //
	bool isName = true;
	for(int i = 0, j = 0, index = 0; i < 256; ++i)
	{
		if(array[i] == ':')
		{
			isName = false;
			j = 0;
		}
		else if(array[i] == ';')
		{
			isName = true;
			index += 1;
		}
		else
		{
			if(isName)
			{
				names[index][j] = array[i];
				j += 1;
			}
			else
			{
				if(atoi(array+i))
				{
					scores[index] = atoi(array+i);
				}
			}
		}
		if(index >= 10)
		{
			break;
		}
	}
	
	// Erase file for repopulation */
	FP = fopen(fileName, "w");
	fclose(FP);
	FP = fopen(fileName, "a");

	bool recorded = false;
	
	char buffer[512] = {0};
	char str_score[8] = {0};
	memset(buffer, 0, 512);

	snprintf(str_score, 8, "%d", score);
	char str_scores[10][8] = {0};

	for(int i = 0; i < 10; ++i)
	{
		snprintf(str_scores[i], 8, "%d", scores[i]);
	}

	/* squeeze in score */
	for(int i = 0; i < (10-recorded); ++i)
	{
		if((score > scores[i]) && !recorded)
		{
			strncat(buffer, name, 14);
			strncat(buffer, ":", 1);
			strncat(buffer, str_score, 8);
			strncat(buffer, ";", 1);
			recorded = true;
		}
			strncat(buffer, names[i], 14);
			strncat(buffer, ":", 1);
			strncat(buffer, str_scores[i], 8);
			strncat(buffer, ";", 1);
	}
	fprintf(FP, "%s", buffer);
	fclose(FP);
}

void
sort_scores(char * fileName)
{
	return;
}

bool
is_worty(int score)
{
	return 1;
}