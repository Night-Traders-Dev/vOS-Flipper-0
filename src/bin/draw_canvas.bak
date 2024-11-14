// bin/draw_canvas.c
#include <furi.h>
#include <gui/canvas.h>
#include <power/power_service/power.h>
#include "../lib/draw_canvas.h"

WindowType current_window = WindowStatus;

void draw_callback(Canvas* canvas, void* ctx) {
    UNUSED(ctx);
    canvas_clear(canvas);

    switch(current_window) {
        case WindowStatus: {
            canvas_set_color(canvas, ColorWhite);
            canvas_draw_box(canvas, 0, 0, canvas_width(canvas), 14);

            canvas_set_color(canvas, ColorBlack);
            canvas_draw_frame(canvas, 0, 0, canvas_width(canvas), 14);

            canvas_set_font(canvas, FontSecondary);
            canvas_set_color(canvas, ColorBlack);
            canvas_draw_str(canvas, 2, 10, "vOS");

            Power* power = furi_record_open(RECORD_POWER);
            PowerInfo power_info;
            power_get_info(power, &power_info);

            char battery_text[10];
            snprintf(battery_text, sizeof(battery_text), "%d%%", power_info.charge);

            canvas_draw_str(canvas, canvas_width(canvas) - 30, 10, battery_text);

            furi_record_close(RECORD_POWER);
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
            canvas_draw_str(canvas, 10, 20, "Version 0.0.1");
            canvas_draw_str(canvas, 10, 40, "Created by blmvxer");
            break;

        default:
            canvas_set_font(canvas, FontSecondary);
            canvas_set_color(canvas, ColorBlack);
            canvas_draw_str(canvas, canvas_width(canvas) / 2 - 30, canvas_height(canvas) / 2, "Unknown Window");
            break;
    }
}
