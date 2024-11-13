// bin/draw_canvas.c
#include <furi.h>
#include <gui/canvas.h>
#include "../lib/draw_canvas.h"

// Define the current window variable
WindowType current_window = WindowStatus;

void draw_callback(Canvas* canvas, void* ctx) {
    UNUSED(ctx);
    canvas_clear(canvas);

    switch(current_window) {
        case WindowStatus:
            // Draw the status bar background
            canvas_set_color(canvas, ColorWhite);
            canvas_draw_box(canvas, 0, 0, canvas_width(canvas), 14);

            // Draw the border around the status bar
            canvas_set_color(canvas, ColorBlack);
            canvas_draw_frame(canvas, 0, 0, canvas_width(canvas), 14);

            // Draw the status bar text
            canvas_set_font(canvas, FontSecondary);
            canvas_set_color(canvas, ColorBlack);
            canvas_draw_str(canvas, 2, 10, "Status Bar");
            break;

        case WindowEmpty:
            // Draw an empty window
            canvas_set_font(canvas, FontSecondary);
            canvas_set_color(canvas, ColorBlack);
            canvas_draw_str(canvas, canvas_width(canvas) / 2 - 30, canvas_height(canvas) / 2, "Empty Window");
            break;

        case WindowAbout:
            // Draw the "About Me" window
            canvas_set_font(canvas, FontSecondary);
            canvas_set_color(canvas, ColorBlack);
            canvas_draw_str(canvas, 10, 20, "About Me");
            canvas_draw_str(canvas, 10, 40, "Created by blmvxer");
            break;

        default:
            // Handle unexpected values, including WindowCount
            canvas_set_font(canvas, FontSecondary);
            canvas_set_color(canvas, ColorBlack);
            canvas_draw_str(canvas, canvas_width(canvas) / 2 - 30, canvas_height(canvas) / 2, "Unknown Window");
            break;
    }
}
