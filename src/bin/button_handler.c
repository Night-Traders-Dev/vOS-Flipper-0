#include <furi.h>
#include <input/input.h>
#include "../lib/button_handler.h"

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
            // Slide the scene over
            FURI_LOG_I("ButtonHandler", "Sliding scene to the left");
        } else if(input_event->key == InputKeyRight) {
            // Open the Flipper App Drawer
            FURI_LOG_I("ButtonHandler", "Opening Flipper App Drawer");
        }
    }
}
