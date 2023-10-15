#include "automaton.h"

#include <string.h>

struct automaton automaton = { .states = { { 0 } }, .accepted = { false }, .start = -1, .len = 0 };

void add_automaton_state(char * name) {
    for (usize i = 0; i < automaton.len; i += 1) {
        if (strcmp(name, automaton.states[i]) == 0) {
            return;
        }
    }

    strcpy(automaton.states[automaton.len], name);
    automaton.len += 1;
}

void remove_automaton_state(usize idx) {
    if (idx >= automaton.len) {
        return;
    }

    if ((isize) idx == automaton.start) {
        automaton.start = -1;
    } else {
        automaton.start -= 1;
    }

    for (usize i = idx; i < automaton.len - 1; i += 1) {
        strcpy(automaton.states[i], automaton.states[i + 1]);
        automaton.accepted[i] = automaton.accepted[i + 1];
    }

    automaton.states[automaton.len - 1][0] = '\0';

    automaton.len -= 1;
}
