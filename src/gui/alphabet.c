#include "alphabet.h"

#include <string.h>

#include "raygui.h"
#include "raylib.h"

#include "../defs.h"
#include "../logic/alphabet.h"

extern struct alphabet alphabet;

static char letter_box_text[128] = "LETTER";
static bool letter_box_edit_mode = false;
static int alphabet_list_index = 0;
static int alphabet_list_active = 0;
static char alphabet_list_buffer[512] = "\0";

void draw_alphabet_box(void) {
    GuiGroupBox((Rectangle) { 8, 8, 152, 304 }, "Alphabet");

    // letter input box
    if (GuiTextBox((Rectangle) { 16, 16, 136, 24 }, letter_box_text, 128, letter_box_edit_mode)) {
        letter_box_edit_mode = !letter_box_edit_mode;
    }

    // add button
    if (GuiButton((Rectangle) { 16, 48, 136, 24 }, "Add")) {
        if (strlen(letter_box_text) == 1) {
            add_alphabet_letter(*letter_box_text);
        }
    }

    // list of alphabet letters
    usize buffer_size = 1;
    usize letters_num = strlen(alphabet.letters);
    if (letters_num != 0) {
        buffer_size = letters_num + (letters_num - 1);
    }

    generate_alphabet_list(buffer_size);

    alphabet_list_active = GuiListView(
        (Rectangle) { 16, 80, 136, 192 }, alphabet_list_buffer, &alphabet_list_index,
        alphabet_list_active
    );

    // removal button
    if (GuiButton((Rectangle) { 16, 280, 136, 24 }, "Remove selected")) {
        remove_alphabet_letter(alphabet_list_active);
    }
}

void generate_alphabet_list(usize buffer_size) {
    for (usize i = 0, j = 0; i < strlen(alphabet.letters); i += 1, j += 2) {
        alphabet_list_buffer[j] = alphabet.letters[i];
        alphabet_list_buffer[j + 1] = ';';
    }

    alphabet_list_buffer[buffer_size] = '\0';
}
