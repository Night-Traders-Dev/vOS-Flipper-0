#include <furi.h>
#include <input/input.h>
#include <gui/view_port.h>
#include "lib/io_manager.h"
#include "lib/gui_manager.h"

extern ViewPort* view_port;

// Define screen size for cursor boundaries
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define STATUS_BAR_HEIGHT 14
#define CURSOR_MOVE_STEP 1 // Step size for cursor movement
#define BACK_PRESS_LIMIT 3
#define TIME_WINDOW_MS 2000
#define CONTINUOUS_MOVE_DELAY 50 // Delay in milliseconds for continuous movement

static FuriTimer* movement_timer;
static InputKey current_key = InputKeyDown;
static bool is_key_held = false;

void handle_cursor_movement() {
    bool moved = false;

    // Move the cursor based on the current key, enforcing boundaries
    if(current_key == InputKeyLeft) {
        cursor_x = (cursor_x > 0) ? cursor_x - CURSOR_MOVE_STEP : SCREEN_WIDTH - 1; // Wrap to the opposite side
        moved = true;
    } else if(current_key == InputKeyRight) {
        cursor_x = (cursor_x < SCREEN_WIDTH - 1) ? cursor_x + CURSOR_MOVE_STEP : 0; // Wrap to the opposite side
        moved = true;
    } else if(current_key == InputKeyUp) {
        cursor_y = (cursor_y > STATUS_BAR_HEIGHT) ? cursor_y - CURSOR_MOVE_STEP : STATUS_BAR_HEIGHT; // Stay above the status bar
        moved = true;
    } else if(current_key == InputKeyDown) {
        cursor_y = (cursor_y < SCREEN_HEIGHT - 1) ? cursor_y + CURSOR_MOVE_STEP : SCREEN_HEIGHT - 1; // Stay within the screen
        moved = true;
    }

    // Check if the cursor moved and update the view
    if(moved) {
        view_port_update(view_port);
    }
}

void movement_timer_callback(void* ctx) {
    UNUSED(ctx);
    if(is_key_held) {
        handle_cursor_movement();
    }
}

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

    // Handle key press and release for continuous movement
    if(input_event->type == InputTypePress) {
        current_key = input_event->key;
        is_key_held = true;
        furi_timer_start(movement_timer, furi_ms_to_ticks(CONTINUOUS_MOVE_DELAY));
    } else if(input_event->type == InputTypeRelease) {
        if(input_event->key == current_key) {
            is_key_held = false;
            furi_timer_stop(movement_timer);
            current_key = InputKeyDown;
        }
    }
}

// Initialize the movement timer
void init_mouse_handler() {
    movement_timer = furi_timer_alloc(movement_timer_callback, FuriTimerTypePeriodic, NULL);
}

// Free the movement timer
void free_mouse_handler() {
    furi_timer_free(movement_timer);
}
