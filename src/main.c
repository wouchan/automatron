#include <stdio.h>

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION

#include "defs.h"
#include "gui/alphabet.h"
#include "gui/grammar.h"
#include "gui/language.h"
#include "logic/util.h"

int main() {
    const int screen_width = 1300;
    const int screen_height = 700;

    // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    init_program();
    InitWindow(screen_width, screen_height, "Automatron");

    while (!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            draw_alphabet_box();
            draw_grammar_box();
            draw_language_box();
        }
        EndDrawing();
    }

    CloseWindow();
    deinit_program();
}
