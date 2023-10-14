#include "language.h"

#include <string.h>

#include "raygui.h"
#include "raylib.h"

#include "../defs.h"
#include "../logic/language.h"

extern struct language language;

static int words_list_index = 0;
static int words_list_active = 0;
static char language_list_buffer[8192] = { 0 };

void draw_language_box(void) {
    GuiGroupBox((Rectangle) { 8, 320, 312, 312 }, "Language");

    if (GuiButton((Rectangle) { 16, 328, 296, 24 }, "Generate language")) {
        generate_language();
    }

    generate_language_list();
    words_list_active = GuiListView(
        (Rectangle) { 16, 360, 296, 264 }, language_list_buffer, &words_list_index,
        words_list_active
    );
}

void generate_language_list(void) {
    if (language.len == 0) {
        language_list_buffer[0] = '\0';
        return;
    }

    usize idx = 0;
    for (usize i = 0; i < language.len; i += 1) {
        memcpy(&language_list_buffer[idx], language.words[i], strlen(language.words[i]));
        idx += strlen(language.words[i]);

        language_list_buffer[idx] = ';';
        idx += 1;
    }

    language_list_buffer[idx - 1] = '\0';
}
