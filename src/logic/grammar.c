#include "grammar.h"
#include "alphabet.h"
#include "language.h"

#include <string.h>

struct grammar grammar = { .inputs = { { 0 } }, .outputs = { { 0 } }, .len = 0 };

void add_grammar_rule(char * input, char * output) {
    if (grammar.len >= GRAMMAR_SIZE) {
        return;
    }

    for (usize i = 0; i < strlen(input); i += 1) {
        if (!is_in_alphabet(input[i])) {
            return;
        }
    }

    for (usize i = 0; i < strlen(output); i += 1) {
        if (!is_in_alphabet(output[i])) {
            return;
        }
    }

    bool includes_nonterminal = false;
    for (usize i = 0; i < strlen(input); i += 1) {
        if (!is_terminal(input[i])) {
            includes_nonterminal = true;
            break;
        }
    }

    if (!includes_nonterminal) {
        return;
    }

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

bool apply_grammar_rule(char * word, usize start_idx, usize rule_idx) {
    isize len = strlen(word);
    isize input_len = strlen(grammar.inputs[rule_idx]);
    isize output_len = strlen(grammar.outputs[rule_idx]);

    isize offset = output_len - input_len;
    if (offset > 0) {
        if (len + offset >= WORD_SIZE) {
            return false;
        }
    }

    if (offset > 0) {
        for (isize i = len + offset - 1; i > (isize) start_idx + output_len - 1; i -= 1) {
            word[i] = word[i - offset];
        }

        word[len + offset] = '\0';
    } else if (offset < 0) {
        for (isize i = start_idx + input_len + offset; i < len + offset; i += 1) {
            word[i] = word[i - offset];
        }

        word[len + offset] = '\0';
    }

    memcpy(&word[start_idx], grammar.outputs[rule_idx], output_len);

    return true;
}
