#include "alphabet.h"

#include <stdlib.h>
#include <string.h>

struct alphabet alphabet = { .letters = { 'S' } };

void add_alphabet_letter(char letter) {
    usize len = strlen(alphabet.letters);

    for (usize i = 0; i < len; i += 1) {
        if (letter == alphabet.letters[i]) {
            return;
        }
    }

    alphabet.letters[len] = letter;
}

void remove_alphabet_letter(usize index) {
    if (index == 0 || index >= 256) {
        return;
    }

    usize len = strlen(alphabet.letters);

    for (usize i = index; i < len - 1; i += 1) {
        alphabet.letters[i] = alphabet.letters[i + 1];
    }

    alphabet.letters[len - 1] = '\0';
}
