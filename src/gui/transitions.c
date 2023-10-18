#include "transitions.h"

#include <string.h>

#include "raygui.h"
#include "raylib.h"

#include "../logic/alphabet.h"
#include "../logic/automaton.h"
#include "../logic/transitions.h"

extern struct alphabet alphabet;
extern struct automaton automaton;
extern struct transitions transitions;

static int state_dropdown_active = 0;
static bool state_dropdown_edit_mode = false;
static char state_dropdown_buffer[1024] = { 0 };
static int transitions_list_index = 0;
static int transitions_list_active = -1;
static char transitions_list_buffer[8192] = { 0 };

void draw_transitions_box(void) {
    GuiGroupBox((Rectangle) { 880, 320, 312, 312 }, "Transitions");

    if (GuiButton((Rectangle) { 888, 360, 144, 24 }, "Apply")) {
        if (transitions_list_active >= 0 && automaton.len > 0 && alphabet.len > 0) {
            usize state = transitions_list_active / alphabet.len;
            usize letter = transitions_list_active % alphabet.len;

            transitions.jumps[state][letter] = state_dropdown_active;
        }
    }

    if (GuiButton((Rectangle) { 1040, 360, 144, 24 }, "Clear selected")) {
        if (transitions_list_active >= 0 && automaton.len > 0 && alphabet.len > 0) {
            usize state = transitions_list_active / alphabet.len;
            usize letter = transitions_list_active % alphabet.len;

            transitions.jumps[state][letter] = -1;
        }
    }

    generate_transitions_list();
    transitions_list_active = GuiListView(
        (Rectangle) { 888, 392, 296, 232 }, transitions_list_buffer, &transitions_list_index,
        transitions_list_active
    );

    generate_state_dropdown();
    if (GuiDropdownBox(
            (Rectangle) { 888, 328, 296, 24 }, state_dropdown_buffer, &state_dropdown_active,
            state_dropdown_edit_mode
        )) {
        state_dropdown_edit_mode = !state_dropdown_edit_mode;
    }
}

void generate_transitions_list(void) {
    if (automaton.len == 0 || alphabet.len == 0) {
        transitions_list_buffer[0] = '\0';
        return;
    }

    usize idx = 0;
    for (usize s = 0; s < automaton.len; s += 1) {
        for (usize c = 0; c < alphabet.len; c += 1) {
            transitions_list_buffer[idx] = '(';
            idx += 1;

            memcpy(&transitions_list_buffer[idx], automaton.states[s], strlen(automaton.states[s]));
            idx += strlen(automaton.states[s]);

            memcpy(&transitions_list_buffer[idx], ", ", 2);
            idx += 2;

            transitions_list_buffer[idx] = alphabet.symbols[c];
            idx += 1;

            memcpy(&transitions_list_buffer[idx], ") -> ", 5);
            idx += 5;

            if (transitions.jumps[s][c] != -1) {
                isize next = transitions.jumps[s][c];

                memcpy(
                    &transitions_list_buffer[idx], automaton.states[next],
                    strlen(automaton.states[next])
                );

                idx += strlen(automaton.states[next]);
            }

            transitions_list_buffer[idx] = ';';
            idx += 1;
        }
    }

    transitions_list_buffer[idx - 1] = '\0';
}

void generate_state_dropdown(void) {
    if (automaton.len == 0) {
        state_dropdown_buffer[0] = '\0';
        return;
    }

    usize idx = 0;
    for (usize s = 0; s < automaton.len; s += 1) {
        memcpy(&state_dropdown_buffer[idx], automaton.states[s], strlen(automaton.states[s]));
        idx += strlen(automaton.states[s]);

        state_dropdown_buffer[idx] = ';';
        idx += 1;
    }

    state_dropdown_buffer[idx - 1] = '\0';
}
