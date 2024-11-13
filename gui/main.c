#include <furi.h>
#include <gui/gui.h>
#include <gui/view_port.h>

// Callback to draw the empty status bar and background
static void draw_callback(Canvas* canvas, void* ctx) {
    UNUSED(ctx);

    // Clear the canvas
    canvas_clear(canvas);

    // Draw the status bar
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_box(canvas, 0, 0, canvas_width(canvas), 14); // Draw the status bar background
    canvas_set_color(canvas, ColorWhite);
    canvas_draw_str(canvas, 2, 10, "Status Bar"); // Example text for the status bar
}

// Input handling callback
static void input_callback(InputEvent* input_event, void* ctx) {
    bool* running = ctx;

    // Check for back button press to exit the app
    if(input_event->type == InputTypeShort && input_event->key == InputKeyBack) {
        *running = false; // Set running to false to exit the app
    }
}

int32_t main_entry(void* p) {
    UNUSED(p);

    // Variable to keep the app running
    bool running = true;

    // Initialize ViewPort
    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, draw_callback, NULL);
    view_port_input_callback_set(view_port, input_callback, &running);

    // Attach the ViewPort to the GUI
    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);

    // Keep the app running until the back button is pressed
    while(running) {
        furi_delay_ms(100);
    }

    // Clean up resources before exiting
    gui_remove_view_port(gui, view_port);
    view_port_free(view_port);
    furi_record_close(RECORD_GUI);

    return 0;
}
