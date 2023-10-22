#pragma once

#include "../defs.h"

#define AUTOMATON_SIZE   64
#define STATE_LABEL_SIZE 64

/// Represents a finite-state machine.
struct automaton {
    /// Alphanumerical labels of the states.
    char states[AUTOMATON_SIZE][STATE_LABEL_SIZE];
    /// Mask marking accepted states.
    bool accepted[AUTOMATON_SIZE];
    /// Index of the initial state.
    isize start;
    /// Current number of states in the machine.
    usize len;
};

/// Adds a state with a given label to the automaton.
/// Does nothing if the label already exists.
void add_automaton_state(char * label);

/// Removes a state at a given index.
void remove_automaton_state(usize idx);
