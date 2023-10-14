#pragma once

#include "../defs.h"

struct alphabet {
    char letters[256];
};

void add_alphabet_letter(char letter);

void remove_alphabet_letter(usize idx);
