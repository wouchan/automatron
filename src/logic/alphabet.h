#pragma once

#include "../defs.h"

#define ALPHABET_SIZE 128

/// Represents some set of symbols.
/// Each symbol can be marked as terminal.
struct alphabet {
    char symbols[ALPHABET_SIZE];
    /// Mask marking terminal symbols.
    bool terminals[ALPHABET_SIZE];
    /// Current number of symbols in the alphabet.
    usize len;
};

/// Adds a given symbol to the alphabet.
/// Does nothing if the alphabet is full or already contains the symbol.
void add_alphabet_symbol(char symbol);

/// Removes an alphabet symbol at a given index.
void remove_alphabet_symbol(usize idx);

/// Returns true if the alphabet contains a given symbol.
bool is_in_alphabet(char symbol);

/// Returns true if a given symbol is terminal.
bool is_terminal(char symbol);
