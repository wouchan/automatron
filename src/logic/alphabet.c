#include "alphabet.h"

#include <stdlib.h>
#include <string.h>

// Global alphabet instance.
struct alphabet alphabet = { 0 };

void add_alphabet_symbol(char symbol) {
    if (alphabet.len >= ALPHABET_SIZE) {
        return;
    }

    for (usize i = 0; i < alphabet.len; i += 1) {
        if (symbol == alphabet.symbols[i]) {
            return;
        }
    }

    alphabet.symbols[alphabet.len] = symbol;
    alphabet.terminals[alphabet.len] = false;

    alphabet.len += 1;
}

void remove_alphabet_symbol(usize idx) {
    if (idx >= alphabet.len) {
        return;
    }

    for (usize i = idx; i < alphabet.len - 1; i += 1) {
        alphabet.symbols[i] = alphabet.symbols[i + 1];
        alphabet.terminals[i] = alphabet.terminals[i + 1];
    }

    alphabet.len -= 1;
}

bool is_in_alphabet(char symbol) {
    for (usize i = 0; i < alphabet.len; i += 1) {
        if (symbol == alphabet.symbols[i]) {
            return true;
        }
    }

    return false;
}

bool is_terminal(char symbol) {
    for (usize i = 0; i < alphabet.len; i += 1) {
        if (symbol == alphabet.symbols[i]) {
            return alphabet.terminals[i];
        }
    }

    return false;
}
