#include "alphabet.h"

#include <stdlib.h>
#include <string.h>

struct alphabet alphabet = { 0 };

void add_alphabet_letter(char letter) {
    for (usize i = 0; i < alphabet.len; i += 1) {
        if (letter == alphabet.letters[i]) {
            return;
        }
    }

    alphabet.letters[alphabet.len] = letter;
    alphabet.terminals[alphabet.len] = false;

    alphabet.len += 1;
}

void remove_alphabet_letter(usize idx) {
    if (idx >= alphabet.len) {
        return;
    }

    for (usize i = idx; i < alphabet.len - 1; i += 1) {
        alphabet.letters[i] = alphabet.letters[i + 1];
        alphabet.terminals[i] = alphabet.terminals[i + 1];
    }

    alphabet.len -= 1;
}

bool is_in_alphabet(char letter) {
    for (usize i = 0; i < alphabet.len; i += 1) {
        if (letter == alphabet.letters[i]) {
            return true;
        }
    }

    return false;
}

bool is_terminal(char letter) {
    for (usize i = 0; i < alphabet.len; i += 1) {
        if (letter == alphabet.letters[i]) {
            return alphabet.terminals[i];
        }
    }

    return false;
}
