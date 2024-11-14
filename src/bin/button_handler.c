// bin/button_handler.c
#include <furi.h>
#include <input/input.h>
#include <gui/view_port.h>
#include "../lib/button_handler.h"
#include "../lib/draw_canvas.h"

extern ViewPort* view_port;

// Define screen size for cursor boundaries
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define CURSOR_MOVE_STEP 1 // Step size for cursor movement
#define BACK_PRESS_LIMIT 3
#define TIME_WINDOW_MS 2000

void button_input_callback(InputEvent* input_event, void* ctx) {
    ButtonHandlerContext* context = ctx;

    if(input_event->type == InputTypeShort && input_event->key == InputKeyBack) {
        context->back_press_count++;
        if(context->back_press_count == 1) {
            context->first_press_time = furi_get_tick();
        } else if(context->back_press_count >= BACK_PRESS_LIMIT) {
            if(furi_get_tick() - context->first_press_time < furi_ms_to_ticks(TIME_WINDOW_MS)) {
                context->running = false;
                return;
            } else {
                // Reset if time window exceeded
                context->back_press_count = 1;
                context->first_press_time = furi_get_tick();
            }
        }
    }

    // Mouse movement logic
    bool moved = false;
    if(input_event->key == InputKeyLeft) {
        if(input_event->type == InputTypeShort || input_event->type == InputTypeLong) {
            cursor_x = (cursor_x > 0) ? cursor_x - CURSOR_MOVE_STEP : 0;
            moved = true;
        }
    } else if(input_event->key == InputKeyRight) {
        if(input_event->type == InputTypeShort || input_event->type == InputTypeLong) {
            cursor_x = (cursor_x < SCREEN_WIDTH - 1) ? cursor_x + CURSOR_MOVE_STEP : SCREEN_WIDTH - 1;
            moved = true;
        }
    } else if(input_event->key == InputKeyUp) {
        if(input_event->type == InputTypeShort || input_event->type == InputTypeLong) {
            cursor_y = (cursor_y > 0) ? cursor_y - CURSOR_MOVE_STEP : 0;
            moved = true;
        }
    } else if(input_event->key == InputKeyDown) {
        if(input_event->type == InputTypeShort || input_event->type == InputTypeLong) {
            cursor_y = (cursor_y < SCREEN_HEIGHT - 1) ? cursor_y + CURSOR_MOVE_STEP : SCREEN_HEIGHT - 1;
            moved = true;
        }
    }

    // Check if the cursor is at the edges and switch scenes accordingly
    if(cursor_x == 0 && moved) {
        current_window = (current_window == 0) ? (WindowCount - 1) : (current_window - 1);
        cursor_x = SCREEN_WIDTH / 2; // Move cursor back to the center
    } else if(cursor_x == SCREEN_WIDTH - 1 && moved) {
        current_window = (current_window + 1) % WindowCount;
        cursor_x = SCREEN_WIDTH / 2; // Move cursor back to the center
    }

    // Update the view if the cursor moved
    if(moved) {
        view_port_update(view_port);
    }
}
