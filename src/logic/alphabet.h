#pragma once

#include "../defs.h"

struct alphabet {
    char letters[128];
    bool terminals[128];
};

void add_alphabet_letter(char letter, bool terminal);

void remove_alphabet_letter(usize idx);

bool is_in_alphabet(char letter);

bool is_terminal(char letter);
