#include "diagram.h"

#include <math.h>
#include <string.h>

#include "raygui.h"
#include "raylib.h"

#include "../defs.h"
#include "../gui/diagram.h"
#include "../logic/alphabet.h"
#include "../logic/automaton.h"
#include "../logic/transitions.h"
#include "raymath.h"

extern struct alphabet alphabet;
extern struct automaton automaton;
extern struct transitions transitions;

extern isize current_state;
extern isize next_state;

void draw_diagram_box(void) {
    GuiGroupBox((Rectangle) { 328, 8, 544, 464 }, "Diagram");

    GuiGrid((Rectangle) { 336, 16, 528, 448 }, "Diagram", 16, 2);

    // Drawing automaton states
    usize circles_in_row = ceil(sqrt(automaton.len));
    // Center of the grid
    Vector2 center = { 336.0 + 528.0 - 528.0 / 2.0, 16.0 + 448.0 - 448.0 / 2.0 };
    static const f32 CIRCLE_DISTANCE = 100.0;

    usize circles_in_row_halved = circles_in_row / 2;
    f32 start_x = center.x - CIRCLE_DISTANCE * circles_in_row_halved;
    f32 start_y = center.y - CIRCLE_DISTANCE * circles_in_row_halved;
    if (circles_in_row % 2 == 0) {
        start_x += CIRCLE_DISTANCE * 0.5;
        start_y += CIRCLE_DISTANCE * 0.5;
    }

    static const f32 CIRCLE_SIZE = 40.0;
    static const f32 INNER_CIRCLE_SIZE = 30.0;

    // Arrows
    {
        usize current_idx = 0;
        while (current_idx < automaton.len) {
            i32 current_x = current_idx % circles_in_row;
            i32 current_y = current_idx / circles_in_row;

            Vector2 current_center = { start_x + CIRCLE_DISTANCE * (f32) current_x,
                                       start_y + CIRCLE_DISTANCE * (f32) current_y };

            for (usize c = 0; c < alphabet.len; c += 1) {
                i32 target_idx = transitions.jumps[current_idx][c];

                if (target_idx != -1) {
                    i32 target_x = target_idx % circles_in_row;
                    i32 target_y = target_idx / circles_in_row;

                    Vector2 target_center = { start_x + CIRCLE_DISTANCE * (f32) target_x,
                                              start_y + CIRCLE_DISTANCE * (f32) target_y };

                    Color arrow_color;
                    if ((isize) current_idx == current_state && target_idx == next_state) {
                        arrow_color = BLUE;
                    } else {
                        arrow_color = DARKGRAY;
                    }

                    // Bezier curve
                    Vector2 direction = Vector2Subtract(target_center, current_center);
                    direction = Vector2Normalize(direction);
                    Vector2 opposite_direction = Vector2Negate(direction);

                    static const f32 BEZIER_ANGLE = 50.0 * DEG2RAD;
                    direction = Vector2Rotate(direction, BEZIER_ANGLE);
                    opposite_direction = Vector2Rotate(opposite_direction, -BEZIER_ANGLE);

                    static const f32 BEZIER_SCALE = 40.0;
                    Vector2 direction_scaled = Vector2Scale(direction, BEZIER_SCALE);
                    Vector2 opposite_direction_scaled =
                        Vector2Scale(opposite_direction, BEZIER_SCALE);

                    Vector2 control = Vector2Add(current_center, direction_scaled);
                    Vector2 opposite_control = Vector2Add(target_center, opposite_direction_scaled);

                    DrawLineBezierCubic(
                        current_center, target_center, control, opposite_control, 5.0, arrow_color
                    );

                    // Arrow
                    static const f32 DISTANCE_FROM_CENTER = 20.0;
                    opposite_direction = Vector2Rotate(opposite_direction, 15.0 * DEG2RAD);
                    Vector2 arrow_peak = Vector2Add(
                        target_center, Vector2Scale(opposite_direction, DISTANCE_FROM_CENTER)
                    );

                    Vector2 right_offset = Vector2Rotate(opposite_direction, 45.0 * DEG2RAD);
                    Vector2 left_offset = Vector2Rotate(opposite_direction, -45.0 * DEG2RAD);

                    static const f32 ARROW_SIZE = 17.5;
                    Vector2 right_vertex =
                        Vector2Add(arrow_peak, Vector2Scale(right_offset, ARROW_SIZE));
                    Vector2 left_vertex =
                        Vector2Add(arrow_peak, Vector2Scale(left_offset, ARROW_SIZE));

                    DrawTriangle(arrow_peak, right_vertex, left_vertex, arrow_color);

                    // Label
                    static const f32 LABEL_OFFSET = 10.0;
                    DrawRectangle(
                        control.x - LABEL_OFFSET, control.y - LABEL_OFFSET, 25, 15, LIGHTGRAY
                    );

                    DrawRectangleLines(
                        control.x - LABEL_OFFSET, control.y - LABEL_OFFSET, 25, 15, GRAY
                    );

                    char text[2] = { 0 };
                    text[0] = alphabet.symbols[c];
                    DrawText(
                        text, control.x - LABEL_OFFSET + 10, control.y - LABEL_OFFSET + 2, 10, BLACK
                    );
                }
            }

            current_idx += 1;
        }
    }

    // Circles
    {
        usize idx = 0;
        while (idx < automaton.len) {

            i32 x = idx % circles_in_row;
            i32 y = idx / circles_in_row;

            Vector2 circle_center = { start_x + CIRCLE_DISTANCE * (f32) x,
                                      start_y + CIRCLE_DISTANCE * (f32) y };

            Rectangle rec = { circle_center.x - CIRCLE_SIZE / 2, circle_center.y - CIRCLE_SIZE / 2,
                              CIRCLE_SIZE, CIRCLE_SIZE };

            Rectangle inner_rec = { circle_center.x - INNER_CIRCLE_SIZE / 2,
                                    circle_center.y - INNER_CIRCLE_SIZE / 2, INNER_CIRCLE_SIZE,
                                    INNER_CIRCLE_SIZE };

            if (automaton.start == (isize) idx) {
                GuiDrawIcon(
                    ICON_ARROW_RIGHT_FILL, circle_center.x - CIRCLE_SIZE, circle_center.y - 8, 1,
                    BLACK
                );
            }

            Color outline_color;
            if ((isize) idx == current_state) {
                outline_color = RED;
            } else {
                outline_color = BLACK;
            }

            DrawRectangleRounded(rec, 1.0, 1.0, RAYWHITE);
            DrawRectangleRoundedLines(rec, 1.0, 1.0, 3.0, outline_color);

            if (automaton.accepted[idx]) {
                DrawRectangleRoundedLines(inner_rec, 1.0, 1.0, 3.0, outline_color);
            }

            Vector2 label_coords = { circle_center.x -
                                         ((f32) strlen(automaton.states[idx]) / 2) * 5.0,
                                     circle_center.y - 5.0 };

            DrawText(automaton.states[idx], label_coords.x, label_coords.y, 10.0, BLACK);

            idx += 1;
        }
    }
}
