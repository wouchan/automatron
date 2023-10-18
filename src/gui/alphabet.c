#include "alphabet.h"

#include <string.h>

#include "raygui.h"
#include "raylib.h"

#include "../defs.h"
#include "../logic/alphabet.h"

extern struct alphabet alphabet;

static char letter_box_text[128] = "SYMBOL";
static bool letter_box_edit_mode = false;
static int alphabet_list_index = 0;
static int alphabet_list_active = -1;
static char alphabet_list_buffer[512] = { 0 };

void draw_alphabet_box(void) {
    GuiGroupBox((Rectangle) { 8, 8, 152, 304 }, "Alphabet");

    // letter input box
    if (GuiTextBox((Rectangle) { 16, 16, 136, 24 }, letter_box_text, 128, letter_box_edit_mode)) {
        letter_box_edit_mode = !letter_box_edit_mode;
    }

    // add button
    if (GuiButton((Rectangle) { 16, 48, 136, 24 }, "Add")) {
        if (strlen(letter_box_text) == 1) {
            add_alphabet_symbol(*letter_box_text);
        }
    }

    // list of alphabet letters
    generate_alphabet_list();
    alphabet_list_active = GuiListView(
        (Rectangle) { 16, 80, 136, 160 }, alphabet_list_buffer, &alphabet_list_index,
        alphabet_list_active
    );

    // terminal button
    if (GuiButton((Rectangle) { 16, 248, 136, 24 }, "Mark terminal")) {
        if (alphabet_list_active >= 0) {
            alphabet.terminals[alphabet_list_active] = !alphabet.terminals[alphabet_list_active];
        }
    }

    // removal button
    if (GuiButton((Rectangle) { 16, 280, 136, 24 }, "Remove selected")) {
        remove_alphabet_symbol(alphabet_list_active);
    }
}

void generate_alphabet_list(void) {
    if (alphabet.len == 0) {
        alphabet_list_buffer[0] = '\0';
        return;
    }

    usize idx = 0;
    for (usize i = 0; i < alphabet.len; i += 1) {
        if (alphabet.terminals[i]) {
            memcpy(&alphabet_list_buffer[idx], "* ", 2);
            idx += 2;
        }

        alphabet_list_buffer[idx] = alphabet.symbols[i];
        alphabet_list_buffer[idx + 1] = ';';

        idx += 2;
    }

    alphabet_list_buffer[idx - 1] = '\0';
}
