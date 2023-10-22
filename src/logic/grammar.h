#pragma once

#include "../defs.h"

#define GRAMMAR_SIZE      64
#define GRAMMAR_RULE_SIZE 64

/// Represents a set of rules transforming
/// one chain of symbols into another in a form
/// of input -> output pairs.
struct grammar {
    char inputs[GRAMMAR_SIZE][GRAMMAR_RULE_SIZE];
    char outputs[GRAMMAR_SIZE][GRAMMAR_RULE_SIZE];
    /// Current number of grammar rules.
    usize len;
};

/// Adds new grammar rule. Does nothing if the rule
/// already exists or the grammar is full.
void add_grammar_rule(char * input, char * output);

/// Removes a rule at the given index.
void remove_grammar_rule(usize idx);

/// Transforms a given word using grammar rule at the given index,
/// starting from character at the `start_idx`.
bool apply_grammar_rule(char * word, usize start_idx, usize rule_idx);
