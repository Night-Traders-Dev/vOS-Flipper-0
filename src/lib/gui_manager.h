#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <gui/canvas.h>
#include <gui/view.h>

typedef enum {
    WindowStatus,
    WindowEmpty,
    WindowAbout,
    WindowCount
} WindowType;

extern WindowType current_window;

// Cursor position
extern int cursor_x;
extern int cursor_y;

void draw_callback(Canvas* canvas, void* ctx);

#endif // GUI_MANAGER_H
