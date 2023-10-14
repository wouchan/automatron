#include <stdio.h>

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION

#include "defs.h"
#include "gui/alphabet.h"
#include "gui/grammar.h"
#include "gui/language.h"

static const int SCREEN_WIDTH = 1300;
static const int SCREEN_HEIGHT = 700;

void main_loop(void) {
    BeginDrawing();
    {
        ClearBackground(RAYWHITE);

        draw_alphabet_box();
        draw_grammar_box();
        draw_language_box();
    }
    EndDrawing();
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Automatron");

    while (!WindowShouldClose()) {
        main_loop();
    }

    CloseWindow();
}
