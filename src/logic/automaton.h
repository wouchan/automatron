#pragma once

#include "../defs.h"

struct automaton {
    char states[64][16];
    bool accepted[64];
    isize start;
    usize len;
};

void add_automaton_state(char * name);

void remove_automaton_state(usize idx);
