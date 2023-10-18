#include "debug.h"

#include <stdio.h>
#include <string.h>

#include "raygui.h"
#include "raylib.h"

#include "../defs.h"
#include "../logic/alphabet.h"
#include "../logic/automaton.h"
#include "../logic/transitions.h"

extern struct alphabet alphabet;
extern struct automaton automaton;
extern struct transitions transitions;

static char debug_box_text[128] = "STRING";
static bool debug_box_edit_mode = false;
static isize current_position = -1;
isize current_state = -1;
isize next_state = -1;

static char current_position_text_buffer[64] = "Current position: ";
static char current_symbol_text_buffer[64] = "Current symbol: ";
static char current_state_text_buffer[64] = "Current state: ";
static char next_symbol_text_buffer[64] = "Next symbol: ";
static char next_state_text_buffer[64] = "Next state: ";

void draw_debug_box(void) {
    GuiGroupBox((Rectangle) { 328, 480, 544, 152 }, "Debug");

    if (GuiTextBox((Rectangle) { 336, 488, 528, 24 }, debug_box_text, 128, debug_box_edit_mode)) {
        debug_box_edit_mode = !debug_box_edit_mode;
    }

    char current_symbol = '\0';
    if (current_position < 0) {
        sprintf(&current_position_text_buffer[18], "-");
        sprintf(&current_symbol_text_buffer[16], "-");
    } else if (current_position < (isize) strlen(debug_box_text)) {
        current_symbol = debug_box_text[current_position];

        sprintf(&current_position_text_buffer[18], "%lu", current_position + 1);
        sprintf(&current_symbol_text_buffer[16], "%c", current_symbol);
    }

    if (current_state < 0) {
        sprintf(&current_state_text_buffer[15], "-");
    } else if (current_state < (isize) automaton.len) {
        sprintf(&current_state_text_buffer[15], "%s", automaton.states[current_state]);
    }

    if (next_state < 0) {
        sprintf(&next_state_text_buffer[12], "-");
    } else if (next_state < (isize) automaton.len) {
        sprintf(&next_state_text_buffer[12], "%s", automaton.states[next_state]);
    }

    isize next_position = current_position + 1;
    if (next_position < (isize) strlen(debug_box_text)) {
        sprintf(&next_symbol_text_buffer[13], "%c", debug_box_text[next_position]);
    } else {
        sprintf(&next_symbol_text_buffer[13], "-");
    }

    if (current_state < 0) {
        next_state = automaton.start;
    } else if (current_symbol != '\0') {
        isize symbol_idx = -1;
        for (usize i = 0; i < alphabet.len; i += 1) {
            if (alphabet.symbols[i] == current_symbol) {
                symbol_idx = i;
                break;
            }
        }

        if (symbol_idx >= 0) {
            next_state = transitions.jumps[current_state][symbol_idx];
        } else {
            next_state = -1;
        }
    } else {
        next_state = -1;
    }

    GuiLabel((Rectangle) { 336, 516, 136, 24 }, current_position_text_buffer);
    GuiLabel((Rectangle) { 336, 538, 136, 24 }, current_symbol_text_buffer);
    GuiLabel((Rectangle) { 336, 560, 136, 24 }, current_state_text_buffer);
    GuiLabel((Rectangle) { 336, 582, 136, 24 }, next_symbol_text_buffer);
    GuiLabel((Rectangle) { 336, 604, 136, 24 }, next_state_text_buffer);

    if (GuiButton((Rectangle) { 728, 520, 136, 24 }, "Reset")) {
        current_position = -1;
        current_state = -1;
        next_state = -1;
    }

    if (GuiButton((Rectangle) { 728, 552, 136, 24 }, "Step over")) {
        if (next_state >= 0) {
            current_position += 1;
            current_state = next_state;
        }
    }

    if (GuiButton((Rectangle) { 728, 584, 136, 24 }, "Run through")) {
        while (next_state >= 0) {
            current_position += 1;
            current_state = next_state;
        }
    }

    DrawText("Status:", 728, 616, 10, BLACK);

    if (current_state >= 0) {
        if (automaton.accepted[current_state]) {
            DrawText("ACCEPTED", 768, 616, 10, GREEN);
        } else {
            DrawText("NOT ACCEPTED", 768, 616, 10, RED);
        }
    } else {
        DrawText("-", 768, 616, 10, BLACK);
    }
}
