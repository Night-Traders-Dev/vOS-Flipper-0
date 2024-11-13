// bin/button_handler.c
#include <furi.h>
#include <input/input.h>
#include "../lib/button_handler.h"

void button_input_callback(InputEvent* input_event, void* ctx) {
    bool* running = ctx;

    if(input_event->type == InputTypeShort && input_event->key == InputKeyBack) {
        *running = false;
    }
}
