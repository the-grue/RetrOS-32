# GFX Library - Window API Documentation

### struct window
Represents a window object with its properties and actions.
Mainly needed to draw to the window using its draw operations.

- See the code for all properties and methods [window.h](https://github.com/joexbayer/RetrOS-32/blob/main/include/gfx/window.h).

## Functions

### gfx_new_window
Creates a new window.

- `struct window* gfx_new_window(int width, int height, window_flag_t flags)`

#### Usage
```c
struct window* win = gfx_new_window(250, 200, GFX_IS_RESIZABLE);
win->draw->rect(win, 0, 0, 250, 200, COLOR_VGA_GREEN);
```
Example: [kclock](https://github.com/joexbayer/RetrOS-32/blob/main/kernel/kthreads/kclock.c).

## Enums

### window_state_t
Represents the motion status of a window.

- `GFX_WINDOW_MOVING`: The window is in a moving state.
- `GFX_WINDOW_STATIC`: The window is in a static state.

### window_flag_t
Flags representing certain properties a window can have.

- `GFX_IS_RESIZABLE`: The window is resizable.
- `GFX_IS_IMMUATABLE`: The window cannot be modified.
- `GFX_IS_MOVABLE`: The window can be moved.
- `GFX_IS_TRANSPARENT`: The window is transparent.
- `GFX_IS_HIDDEN`: The window is hidden.
- `GFX_HIDE_HEADER`: The window header is hidden.
- `GFX_HIDE_BORDER`: The window border is hidden.
- `GFX_NO_OPTIONS`: The window options are hidden.

## Structs

### window_ops
Struct for window operations.
These can be overwritten by a kernel thread, but doing so may reduce the usability of the window.
Hover and click are used to move the window. For receiving window interactions use the GFX events (link to gfx events)

- `void (*click)(struct window*, int x, int y)`: Triggered when the window is clicked.
- `void (*hover)(struct window*, int x, int y)`: Triggered when mouse hovers over the window.
- `void (*mousedown)(struct window*, int x, int y)`: Triggered when mouse button is pressed down on the window.
- `void (*mouseup)(struct window*, int x, int y)`: Triggered when mouse button is released over the window.
- `void (*resize)(struct window*, int width, int height)`: Resizes the window.
- `void (*move)(struct window*, int x, int y)`: Moved window to given x, y coordinates
- `int (*destroy)(struct window*)`: Destroys the window.
- `int (*maximize)(struct window*)`: Maximizes the window.

### window_draw_ops
Struct for window drawing operations.

- `void (*draw)(struct window*)`: Draws the window.
- `void (*rect)(struct window*, int x, int y, int width, int height, color_t color)`: Draws a rectangle.
- `void (*textf)(struct window*, int x, int y, color_t color, char* fmt, ...)`: Formats and outputs text.
- `void (*text)(struct window*, int x, int y, char* text, color_t color)`: Outputs text.
- `void (*line)(struct window*, int x1, int y1, int x2, int y2, color_t color)`: Draws a line.
- `void (*circle)(struct window*, int x, int y, int radius, color_t color)`: Draws a circle.
- `int (*box)(struct window*, int x, int y, int width, int height, color_t color)`: Draws a box.

#### Examples
```c
win->draw->rect(win, 0, 0, 250, 200, COLOR_VGA_GREEN);
win->draw->textf(win, 10, 10, COLOR_VGA_WHITE, "Hello, %s!", "World");
win->draw->line(win, 0, 0, 250, 200, COLOR_VGA_RED);
win->draw->circle(win, 125, 100, 50, COLOR_VGA_BLUE);
win->draw->box(win, 0, 0, 250, 200, COLOR_VGA_YELLOW);
```