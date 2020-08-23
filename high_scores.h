#ifndef HIGH_SCORES_H
#define HIGH_SCORES_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "file_io.h"

#define HIGH_SCORE "high_scores.txt"

void add_score(char * fileName, char * name, int score);
void sort_scores(char * fileName);

bool is_worty(int score);

#endif // HIGH_SCORES_H