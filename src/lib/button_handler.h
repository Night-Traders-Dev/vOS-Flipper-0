// lib/button_handler.h
#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include <furi.h>
#include <input/input.h>

// Struct to hold the button press state
typedef struct {
    bool running;
    uint8_t back_press_count;
    uint32_t first_press_time;
} ButtonHandlerContext;

// Function prototype for the input callback
void button_input_callback(InputEvent* input_event, void* ctx);

#endif // BUTTON_HANDLER_H
