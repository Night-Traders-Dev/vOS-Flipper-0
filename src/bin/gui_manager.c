#include <furi.h>
#include <gui/canvas.h>
#include <power/power_service/power.h>
#include <vos_flipper_icons.h>
#include "../lib/gui_manager.h"

// Define screen size for cursor boundaries
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define STATUS_BAR_HEIGHT 14

// Initial cursor position
int cursor_x = 64;
int cursor_y = 32;

WindowType current_window = WindowStatus;

void draw_callback(Canvas* canvas, void* ctx) {
    UNUSED(ctx);
    canvas_clear(canvas);

    // Draw the status bar on every window
    canvas_set_color(canvas, ColorWhite);
    canvas_draw_box(canvas, 0, 0, SCREEN_WIDTH, STATUS_BAR_HEIGHT); // Draw status bar background
    canvas_set_color(canvas, ColorBlack);
    canvas_draw_frame(canvas, 0, 0, SCREEN_WIDTH, STATUS_BAR_HEIGHT); // Draw border around status bar
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 2, 10, "vOS"); // Status bar text

    // Display battery percentage in the status bar
    Power* power = furi_record_open(RECORD_POWER);
    PowerInfo power_info;
    power_get_info(power, &power_info);
    char battery_text[10];
    snprintf(battery_text, sizeof(battery_text), "%d%%", power_info.charge);
    canvas_draw_str(canvas, SCREEN_WIDTH - 30, 10, battery_text);
//    canvas_draw_icon(canvas, SCREEN_WIDTH - 10, 3, &I_Attention_5x8);
    furi_record_close(RECORD_POWER);

    switch(current_window) {
        case WindowStatus:
            // Draw status-specific content (if any)
            break;
        case WindowEmpty:
            canvas_set_color(canvas, ColorBlack);
            canvas_draw_str(canvas, SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2, "Empty Window");
            break;
        case WindowAbout:
            canvas_set_font(canvas, FontSecondary);
            canvas_draw_str(canvas, 10, 20, "Version 0.0.1");
            canvas_draw_str(canvas, 10, 40, "Created by blmvxer");
            break;
        default:
            canvas_draw_str(canvas, SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2, "Unknown Window");
            break;
    }

    // Draw the mouse cursor in all windows, ensuring it stays within boundaries
    canvas_set_color(canvas, ColorBlack);
    canvas_draw_icon(canvas, cursor_x, cursor_y, &I_Attention_5x8);
}
