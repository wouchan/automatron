#include "alphabet.h"

#include "raygui.h"
#include "raylib.h"

#include "../defs.h"

static int words_list_index = 0;
static int words_list_active = 0;

void draw_language_box(void) {
    GuiGroupBox((Rectangle) { 8, 320, 312, 160 }, "Language");

    words_list_active = GuiListView(
        (Rectangle) { 16, 328, 296, 144 }, "a;aaaa;aaaaaaaaa", &words_list_index, words_list_active
    );
}
