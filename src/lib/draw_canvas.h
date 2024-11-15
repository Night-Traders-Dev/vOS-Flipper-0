// lib/draw_canvas.h
#ifndef DRAW_CANVAS_H
#define DRAW_CANVAS_H

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

#endif // DRAW_CANVAS_H
