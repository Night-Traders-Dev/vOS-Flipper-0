// lib/button_handler.h
#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include <furi.h>
#include <input/input.h>

typedef struct {
    bool running;
    uint8_t back_press_count;
    uint32_t first_press_time;
} ButtonHandlerContext;

void button_input_callback(InputEvent* input_event, void* ctx);
void init_button_handler();
void free_button_handler();

#endif // BUTTON_HANDLER_H
