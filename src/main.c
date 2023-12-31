#include <stdio.h>

#include "gui/debug.h"
#include "logic/transitions.h"
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION

#include "defs.h"
#include "gui/alphabet.h"
#include "gui/automaton.h"
#include "gui/debug.h"
#include "gui/diagram.h"
#include "gui/grammar.h"
#include "gui/language.h"
#include "gui/transitions.h"

static const int SCREEN_WIDTH = 1200;
static const int SCREEN_HEIGHT = 640;

void main_loop(void) {
    BeginDrawing();
    {
        ClearBackground(RAYWHITE);

        draw_alphabet_box();
        draw_grammar_box();
        draw_language_box();
        draw_automaton_box();
        draw_transitions_box();
        draw_diagram_box();
        draw_debug_box();
    }
    EndDrawing();
}

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Automatron");

    init_transitions_array();

    while (!WindowShouldClose()) {
        main_loop();
    }

    CloseWindow();
}
