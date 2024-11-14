// bin/button_handler.c
#include <furi.h>
#include <input/input.h>
#include <gui/view_port.h>
#include "../lib/button_handler.h"
#include "../lib/draw_canvas.h"

extern ViewPort* view_port;

#define BACK_PRESS_LIMIT 3
#define TIME_WINDOW_MS 2000

void button_input_callback(InputEvent* input_event, void* ctx) {
    ButtonHandlerContext* context = ctx;

    if(input_event->type == InputTypeShort) {
        if(input_event->key == InputKeyBack) {
            context->back_press_count++;
            if(context->back_press_count == 1) {
                context->first_press_time = furi_get_tick();
            } else if(context->back_press_count >= BACK_PRESS_LIMIT) {
                if(furi_get_tick() - context->first_press_time < furi_ms_to_ticks(TIME_WINDOW_MS)) {
                    context->running = false;
                } else {
                    context->back_press_count = 1;
                    context->first_press_time = furi_get_tick();
                }
            }
        } else if(input_event->key == InputKeyLeft) {
            current_window = (current_window == 0) ? (WindowCount - 1) : (current_window - 1);
            FURI_LOG_I("ButtonHandler", "Switched to the left window");
            view_port_update(view_port);
        } else if(input_event->key == InputKeyRight) {
            current_window = (current_window + 1) % WindowCount;
            FURI_LOG_I("ButtonHandler", "Switched to the right window");
            view_port_update(view_port);
        }
    }
}
