#ifndef IO_MANAGER_H
#define IO_MANAGER_H

#include <furi.h>
#include <input/input.h>

typedef struct {
    bool running;
    uint8_t back_press_count;
    uint32_t first_press_time;
} ButtonHandlerContext;

void button_input_callback(InputEvent* input_event, void* ctx);
void init_mouse_handler();
void free_mouse_handler();

#endif // IO_MANAGER_H
