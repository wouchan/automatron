#pragma once

#include "../defs.h"

struct grammar {
    char inputs[64][16];
    char outputs[64][16];
    usize len;
};

void add_grammar_rule(char * input, char * output);

void remove_grammar_rule(usize idx);
