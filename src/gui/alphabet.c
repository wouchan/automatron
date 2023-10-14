#include "alphabet.h"

#include <string.h>

#include "raygui.h"
#include "raylib.h"

#include "../defs.h"
#include "../logic/alphabet.h"

extern struct alphabet alphabet;

static char letter_box_text[128] = "LETTER";
static bool letter_box_edit_mode = false;
static bool terminal_checked = false;
static int alphabet_list_index = 0;
static int alphabet_list_active = 0;
static char alphabet_list_buffer[512] = { 0 };

void draw_alphabet_box(void) {
    GuiGroupBox((Rectangle) { 8, 8, 152, 304 }, "Alphabet");

    // letter input box
    if (GuiTextBox((Rectangle) { 16, 16, 136, 24 }, letter_box_text, 128, letter_box_edit_mode)) {
        letter_box_edit_mode = !letter_box_edit_mode;
    }

    // terminal and add buttons
    terminal_checked = GuiCheckBox((Rectangle) { 16, 48, 24, 24 }, "Terminal", terminal_checked);

    if (GuiButton((Rectangle) { 96, 48, 56, 24 }, "Add")) {
        if (strlen(letter_box_text) == 1) {
            add_alphabet_letter(*letter_box_text, terminal_checked);
        }
    }

    // list of alphabet letters
    generate_alphabet_list();
    alphabet_list_active = GuiListView(
        (Rectangle) { 16, 80, 136, 192 }, alphabet_list_buffer, &alphabet_list_index,
        alphabet_list_active
    );

    // removal button
    if (GuiButton((Rectangle) { 16, 280, 136, 24 }, "Remove selected")) {
        remove_alphabet_letter(alphabet_list_active);
    }
}

void generate_alphabet_list(void) {
    usize len = strlen(alphabet.letters);

    usize idx = 0;
    for (usize i = 0; i < len; i += 1) {
        if (alphabet.terminals[i]) {
            memcpy(&alphabet_list_buffer[idx], "* ", 2);
            idx += 2;
        }

        alphabet_list_buffer[idx] = alphabet.letters[i];
        alphabet_list_buffer[idx + 1] = ';';

        idx += 2;
    }

    alphabet_list_buffer[idx - 1] = '\0';
}
