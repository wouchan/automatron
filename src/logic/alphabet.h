#pragma once

#include "../defs.h"

struct alphabet {
    char symbols[128];
    bool terminals[128];
    usize len;
};

void add_alphabet_symbol(char symbol);

void remove_alphabet_symbol(usize idx);

bool is_in_alphabet(char symbol);

bool is_terminal(char symbol);
