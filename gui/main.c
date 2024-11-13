#include <furi.h>
#include <gui/gui.h>
#include <gui/view_port.h>
#include "lib/button_handler.h"

static void draw_callback(Canvas* canvas, void* ctx) {
    UNUSED(ctx);

    canvas_clear(canvas);

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_box(canvas, 0, 0, canvas_width(canvas), 14); // Draw the status bar background
    canvas_set_color(canvas, ColorWhite);
    canvas_draw_str(canvas, 2, 10, "Status Bar"); // Example text for the status bar
}

int32_t main_entry(void* p) {
    UNUSED(p);

    bool running = true;

    // Initialize ViewPort
    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, draw_callback, NULL);
    view_port_input_callback_set(view_port, button_input_callback, &running); // Use the new input callback

    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);

    while(running) {
        furi_delay_ms(100);
    }

    gui_remove_view_port(gui, view_port);
    view_port_free(view_port);
    furi_record_close(RECORD_GUI);

    return 0;
}
