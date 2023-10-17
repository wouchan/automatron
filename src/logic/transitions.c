#include "transitions.h"

struct transitions transitions = { 0 };

void init_transitions_array(void) {
    for (usize s = 0; s < 64; s += 1) {
        for (usize c = 0; c < 128; c += 1) {
            transitions.jumps[s][c] = -1;
        }
    }
}
