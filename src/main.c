// main.c
#include <furi.h>
#include <gui/gui.h>
#include <gui/view_port.h>

#include "lib/button_handler.h"
#include "lib/draw_canvas.h"

ViewPort* view_port;

int32_t main_entry(void* p) {
    UNUSED(p);

    ButtonHandlerContext context = {
        .running = true,
        .back_press_count = 0,
        .first_press_time = 0
    };

    view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, draw_callback, NULL);
    view_port_input_callback_set(view_port, button_input_callback, &context);

    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);

    while(context.running) {
        furi_delay_ms(100);
    }

    gui_remove_view_port(gui, view_port);
    view_port_free(view_port);
    furi_record_close(RECORD_GUI);

    return 0;
}
