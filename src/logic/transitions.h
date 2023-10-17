#pragma once

#include "../defs.h"

struct transitions {
    isize jumps[64][128];
};

void init_transitions_array(void);
