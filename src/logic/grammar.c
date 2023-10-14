#include "grammar.h"

#include <string.h>

struct grammar grammar = { .inputs = { { 0 } }, .outputs = { { 0 } }, .len = 0 };

void add_grammar_rule(char * input, char * output) {
    for (usize i = 0; i < grammar.len; i += 1) {
        if (strcmp(input, grammar.inputs[i]) == 0 && strcmp(output, grammar.outputs[i]) == 0) {
            return;
        }
    }

    strcpy(grammar.inputs[grammar.len], input);
    strcpy(grammar.outputs[grammar.len], output);

    grammar.len += 1;
}

void remove_grammar_rule(usize idx) {
    if (idx >= grammar.len) {
        return;
    }

    for (usize i = idx; i < grammar.len - 1; i += 1) {
        strcpy(grammar.inputs[i], grammar.inputs[i + 1]);
        strcpy(grammar.outputs[i], grammar.outputs[i + 1]);
    }

    grammar.inputs[grammar.len - 1][0] = '\0';
    grammar.outputs[grammar.len - 1][0] = '\0';

    grammar.len -= 1;
}
