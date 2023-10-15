#include "automaton.h"

#include <string.h>

#include "raygui.h"
#include "raylib.h"

#include "../logic/automaton.h"

extern struct automaton automaton;

static char state_box_text[16] = "STATE";
static bool state_box_edit_mode = false;
static int automaton_list_index = 0;
static int automaton_list_active = -1;
static char automaton_list_buffer[1024] = { 0 };

void draw_automaton_box(void) {
    GuiGroupBox((Rectangle) { 880, 8, 312, 304 }, "Automaton");

    if (GuiTextBox((Rectangle) { 888, 16, 232, 24 }, state_box_text, 128, state_box_edit_mode)) {
        state_box_edit_mode = !state_box_edit_mode;
    }

    if (GuiButton((Rectangle) { 1128, 16, 56, 24 }, "Add")) {
        if (strlen(state_box_text) > 0) {
            add_automaton_state(state_box_text);
        }
    }

    generate_automaton_list();
    automaton_list_active = GuiListView(
        (Rectangle) { 888, 48, 296, 224 }, automaton_list_buffer, &automaton_list_index,
        automaton_list_active
    );

    if (GuiButton((Rectangle) { 888, 280, 92, 24 }, "Accepted")) {
        if (automaton_list_active >= 0) {
            automaton.accepted[automaton_list_active] = !automaton.accepted[automaton_list_active];
        }
    }

    if (GuiButton((Rectangle) { 988, 280, 96, 24 }, "Mark start")) {
        if (automaton_list_active >= 0) {
            automaton.start = automaton_list_active;
        }
    }

    if (GuiButton((Rectangle) { 1092, 280, 92, 24 }, "Remove")) {
        remove_automaton_state(automaton_list_active);
    }
}

void generate_automaton_list(void) {
    if (automaton.len == 0) {
        automaton_list_buffer[0] = '\0';
        return;
    }

    usize idx = 0;
    for (usize i = 0; i < automaton.len; i += 1) {
        if ((isize) i == automaton.start) {
            memcpy(&automaton_list_buffer[idx], "-> ", 3);
            idx += 3;
        }

        if (automaton.accepted[i]) {
            memcpy(&automaton_list_buffer[idx], "* ", 2);
            idx += 2;
        }

        memcpy(&automaton_list_buffer[idx], automaton.states[i], strlen(automaton.states[i]));
        idx += strlen(automaton.states[i]);

        automaton_list_buffer[idx] = ';';
        idx += 1;
    }

    automaton_list_buffer[idx - 1] = '\0';
}
