// bin/draw_canvas.c
#include <furi.h>
#include <gui/canvas.h>
#include "../lib/draw_canvas.h"

void draw_callback(Canvas* canvas, void* ctx) {
    UNUSED(ctx);

    canvas_clear(canvas);

    // Draw a border around the screen
    canvas_draw_frame(canvas, 0, 0, canvas_width(canvas), canvas_height(canvas));

    // Draw a status bar at the top
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_box(canvas, 0, 0, canvas_width(canvas), 14);
    canvas_set_color(canvas, ColorWhite);
    canvas_draw_str(canvas, 2, 10, "Status Bar");
}
