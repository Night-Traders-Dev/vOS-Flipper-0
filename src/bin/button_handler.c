// bin/button_handler.c
#include <furi.h>
#include <input/input.h>
#include <gui/view_port.h>
#include "../lib/button_handler.h"
#include "../lib/draw_canvas.h"

// Define a global pointer to the ViewPort
extern ViewPort* view_port;

#define BACK_PRESS_LIMIT 3        // Number of presses needed
#define TIME_WINDOW_MS 2000       // Time window in milliseconds

void button_input_callback(InputEvent* input_event, void* ctx) {
    ButtonHandlerContext* context = ctx;

    if(input_event->type == InputTypeShort) {
        if(input_event->key == InputKeyBack) {
            context->back_press_count++;
            if(context->back_press_count == 1) {
                context->first_press_time = furi_get_tick();
            } else if(context->back_press_count >= BACK_PRESS_LIMIT) {
                if(furi_get_tick() - context->first_press_time < furi_ms_to_ticks(TIME_WINDOW_MS)) {
                    context->running = false; // Exit if pressed 3 times within the time window
                } else {
                    context->back_press_count = 1; // Reset if the time window has passed
                    context->first_press_time = furi_get_tick();
                }
            }
        } else if(input_event->key == InputKeyLeft) {
            // Navigate to the previous window
            current_window = (current_window == 0) ? (WindowCount - 1) : (current_window - 1);
            FURI_LOG_I("ButtonHandler", "Switched to the left window");
            view_port_update(view_port); // Refresh the ViewPort
        } else if(input_event->key == InputKeyRight) {
            // Navigate to the next window
            current_window = (current_window + 1) % WindowCount;
            FURI_LOG_I("ButtonHandler", "Switched to the right window");
            view_port_update(view_port); // Refresh the ViewPort
        }
    }
}
