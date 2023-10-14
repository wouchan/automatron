#include "alphabet.h"

#include "raygui.h"
#include "raylib.h"

#include "../defs.h"

static char input_text[128] = "INPUT";
static bool input_edit_mode = false;
static char output_text[128] = "OUTPUT";
static bool output_edit_mode = false;
static int rules_list_index = 0;
static int rules_list_active = 0;

void draw_grammar_box(void) {
    GuiGroupBox((Rectangle) { 168, 8, 152, 304 }, "Grammar");

    if (GuiTextBox((Rectangle) { 176, 16, 136, 24 }, input_text, 128, input_edit_mode)) {
        input_edit_mode = !input_edit_mode;
    }

    if (GuiTextBox((Rectangle) { 176, 48, 136, 24 }, output_text, 128, output_edit_mode)) {
        output_edit_mode = !output_edit_mode;
    }

    if (GuiButton((Rectangle) { 176, 80, 136, 24 }, "Add")) {
    }

    rules_list_active = GuiListView(
        (Rectangle) { 176, 112, 136, 160 }, "S -> ZAR;Z -> ZA;Z -> LX", &rules_list_index,
        rules_list_active
    );

    if (GuiButton((Rectangle) { 176, 280, 136, 24 }, "Remove selected")) {
    }
}
