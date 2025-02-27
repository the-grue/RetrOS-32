#ifndef __TEXED_SCREEN_H__
#define __TEXED_SCREEN_H__

#ifndef NCURSES
#include <args.h>
#else
#include <ncurses.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#endif // !NCURSES


#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25


#ifdef NCURSES
#define ARROW_UP KEY_UP
#define ARROW_DOWN KEY_DOWN
#define ARROW_LEFT KEY_LEFT
#define ARROW_RIGHT KEY_RIGHT

#define BACKSPACE 127
#define ENTER '\n'

#define CTRLC 3   // ASCII for Ctrl+C
#define CTRLE 5   // ASCII for Ctrl+E
#define CTRLS 19  // ASCII for Ctrl+S
#define CTRLF 6   // ASCII for Ctrl+F

#else 

#define ARROW_UP 254
#define ARROW_DOWN 253
#define ARROW_LEFT 252
#define ARROW_RIGHT 251

#define BACKSPACE '\b'
#define ENTER '\n'

#define TAB 9

#define CTRLC 227
#define CTRLE 229
#define CTRLS 243
#define CTRLF 230

#endif

#define COLOR(fg, bg) (fg | bg << 4)

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

int screen_put_char(int x, int y, unsigned char c, unsigned char color);
int screen_write(int x, int y, const char* str, unsigned char color);
int screen_printf(int x, int y, unsigned char color, char* fmt, ...);
int screen_get_char();
int screen_clear(int from , int to, unsigned char color);
void screen_draw_box(int x, int y, int width, int height, char border_color);
int screen_clear_line(int y, unsigned char color);
int screen_set_cursor(int x, int y);

#endif // __TEXED_SCREEN_H__