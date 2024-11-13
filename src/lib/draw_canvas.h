// lib/draw_canvas.h
#ifndef DRAW_CANVAS_H
#define DRAW_CANVAS_H

#include <gui/canvas.h>

typedef enum {
    WindowStatus,
    WindowEmpty,
    WindowAbout,
    WindowCount
} WindowType;

extern WindowType current_window;

void draw_callback(Canvas* canvas, void* ctx);

#endif // DRAW_CANVAS_H
