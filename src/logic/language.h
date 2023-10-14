#pragma once

#include "../defs.h"

#define WORD_SIZE     32
#define QUEUE_SIZE    32
#define LANGUAGE_SIZE 256

struct language {
    char words[LANGUAGE_SIZE][WORD_SIZE];
    usize len;
};

struct word_queue {
    char words[QUEUE_SIZE][WORD_SIZE];
    usize len;
};

bool add_language_word(char * word);

void generate_language(void);

void apply_possible_rules(void);

bool add_to_word_queue(char * word, bool queue_idx);
