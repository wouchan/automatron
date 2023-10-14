#include "alphabet.h"

#include <stdlib.h>
#include <string.h>

struct alphabet alphabet = { .letters = { 'S' }, .terminals = { 0 } };

void add_alphabet_letter(char letter, bool terminal) {
    usize len = strlen(alphabet.letters);

    for (usize i = 0; i < len; i += 1) {
        if (letter == alphabet.letters[i]) {
            return;
        }
    }

    alphabet.letters[len] = letter;
    alphabet.terminals[len] = terminal;
}

void remove_alphabet_letter(usize idx) {
    if (idx == 0 || idx >= 128) {
        return;
    }

    usize len = strlen(alphabet.letters);

    for (usize i = idx; i < len - 1; i += 1) {
        alphabet.letters[i] = alphabet.letters[i + 1];
        alphabet.terminals[i] = alphabet.terminals[i + 1];
    }

    alphabet.letters[len - 1] = '\0';
}

bool is_in_alphabet(char letter) {
    for (usize i = 0; i < strlen(alphabet.letters); i += 1) {
        if (letter == alphabet.letters[i]) {
            return true;
        }
    }

    return false;
}

bool is_terminal(char letter) {
    for (usize i = 0; i < strlen(alphabet.letters); i += 1) {
        if (letter == alphabet.letters[i]) {
            return alphabet.terminals[i];
        }
    }

    return false;
}
