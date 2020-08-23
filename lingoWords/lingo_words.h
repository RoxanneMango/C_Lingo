#ifndef LINGO_WORDS_H
#define LINGO_WORDS_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define LOWER_LETTER_A 97
#define LOWER_LETTER_Z 122

#define MAX_LEN 512

#define FIVE_LETTERS "five_letter_words.txt"
#define SIX_LETTERS "six_letter_words.txt"
#define SEVEN_LETTERS "seven_letter_words.txt"

bool is_letter(char letter);
void find_words(char * file_in);

#endif // LINGO_WORDS_H