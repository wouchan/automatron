#include "alphabet.h"

#include <string.h>

#include "raygui.h"
#include "raylib.h"

#include "../defs.h"
#include "../logic/grammar.h"
#include "grammar.h"

extern struct grammar grammar;

static char input_text[128] = "INPUT";
static bool input_edit_mode = false;
static char output_text[128] = "OUTPUT";
static bool output_edit_mode = false;
static int rules_list_index = 0;
static int rules_list_active = 0;
static char rules_list_buffer[2048] = { 0 };

void draw_grammar_box(void) {
    GuiGroupBox((Rectangle) { 168, 8, 152, 304 }, "Grammar");

    if (GuiTextBox((Rectangle) { 176, 16, 136, 24 }, input_text, 128, input_edit_mode)) {
        input_edit_mode = !input_edit_mode;
    }

    if (GuiTextBox((Rectangle) { 176, 48, 136, 24 }, output_text, 128, output_edit_mode)) {
        output_edit_mode = !output_edit_mode;
    }

    if (GuiButton((Rectangle) { 176, 80, 136, 24 }, "Add")) {
        add_grammar_rule(input_text, output_text);
    }

    generate_grammar_list();
    rules_list_active = GuiListView(
        (Rectangle) { 176, 112, 136, 160 }, rules_list_buffer, &rules_list_index, rules_list_active
    );

    if (GuiButton((Rectangle) { 176, 280, 136, 24 }, "Remove selected")) {
        remove_grammar_rule(rules_list_active);
    }
}

void generate_grammar_list(void) {
    if (grammar.len == 0) {
        rules_list_buffer[0] = '\0';
        return;
    }

    usize idx = 0;
    for (usize i = 0; i < grammar.len; i += 1) {
        memcpy(&rules_list_buffer[idx], grammar.inputs[i], strlen(grammar.inputs[i]));
        idx += strlen(grammar.inputs[i]);

        memcpy(&rules_list_buffer[idx], " -> ", 4);
        idx += 4;

        memcpy(&rules_list_buffer[idx], grammar.outputs[i], strlen(grammar.outputs[i]));
        idx += strlen(grammar.outputs[i]);

        rules_list_buffer[idx] = ';';
        idx += 1;
    }

    rules_list_buffer[idx - 1] = '\0';
}
