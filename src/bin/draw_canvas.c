// bin/draw_canvas.c
#include <furi.h>
#include <gui/canvas.h>
#include <power/power_service/power.h> // Include the Power header
#include "../lib/draw_canvas.h"

// Define the current window variable
WindowType current_window = WindowStatus;

void draw_callback(Canvas* canvas, void* ctx) {
    UNUSED(ctx);
    canvas_clear(canvas);

    switch(current_window) {
        case WindowStatus: {
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

            // Get and display the battery percentage using Power API
            Power* power = furi_record_open(RECORD_POWER); // Open the Power service
            PowerInfo power_info;
            power_get_info(power, &power_info); // Retrieve power info

            char battery_text[10];
            snprintf(battery_text, sizeof(battery_text), "%d%%", power_info.charge);

            // Draw the battery percentage on the status bar
            canvas_draw_str(canvas, canvas_width(canvas) - 30, 10, battery_text);

            furi_record_close(RECORD_POWER); // Close the Power service when done
            break;
        }
        case WindowEmpty:
            canvas_set_font(canvas, FontSecondary);
            canvas_set_color(canvas, ColorBlack);
            canvas_draw_str(canvas, canvas_width(canvas) / 2 - 30, canvas_height(canvas) / 2, "Empty Window");
            break;

        case WindowAbout:
            canvas_set_font(canvas, FontSecondary);
            canvas_set_color(canvas, ColorBlack);
            canvas_draw_str(canvas, 10, 20, "About Me");
            canvas_draw_str(canvas, 10, 40, "Created by blmvxer");
            break;

        default:
            canvas_set_font(canvas, FontSecondary);
            canvas_set_color(canvas, ColorBlack);
            canvas_draw_str(canvas, canvas_width(canvas) / 2 - 30, canvas_height(canvas) / 2, "Unknown Window");
            break;
    }
}
