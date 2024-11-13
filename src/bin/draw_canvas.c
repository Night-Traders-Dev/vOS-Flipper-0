// bin/draw_canvas.c
#include <furi.h>
#include <gui/canvas.h>
#include "../lib/draw_canvas.h"

extern const Icon I_Hidden_window_9x8; // Example icon

void draw_callback(Canvas* canvas, void* ctx) {
    UNUSED(ctx);

    canvas_clear(canvas);

    canvas_draw_frame(canvas, 0, 0, canvas_width(canvas), canvas_height(canvas));

    canvas_set_color(canvas, ColorWhite);
    canvas_draw_box(canvas, 0, 0, canvas_width(canvas), 14);

    canvas_set_font(canvas, FontSecondary);
    canvas_set_color(canvas, ColorBlack); // Set the color for text
    canvas_draw_str(canvas, 2, 10, "Status Bar");

    uint8_t x = canvas_width(canvas) - 10; // Starting position for right-side icons
    bool need_attention = true; // Example flag for notifications

    if (need_attention) {
        canvas_draw_icon(canvas, x - 9, 2, &I_Hidden_window_9x8);
        x -= 12; // Move the x position left for the next icon
    }

    // Example: Draw additional icons or indicators as needed
    // You can add more icons or indicators by updating the x position and repeating the above logic

    // Draw a frame around the status bar
    canvas_draw_rframe(canvas, 0, 0, canvas_width(canvas), 14, 1);
}
