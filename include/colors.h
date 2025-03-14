#ifndef D0F51827_3250_49B2_9614_254FFF11BBC3
#define D0F51827_3250_49B2_9614_254FFF11BBC3


typedef unsigned char color_t;

/* Possible background colors 18, 41, 45 */

#define COLOR_TURQUISE 50 // 50

enum grays {
    COLOR_VGA_DARKEST_GRAY = 17,
    COLOR_VGA_DARK_GRAY = 19,
    COLOR_VGA_MEDIUM_DARK_GRAY = 21,
    COLOR_VGA_MEDIUM_GRAY = 23,
    COLOR_VGA_MEDIUM_LIGHT_GRAY = 25,
    COLOR_VGA_LIGHT_GRAY = 27,
    COLOR_VGA_LIGHTER_GRAY = 29,
    COLOR_VGA_LIGHTEST_GRAY = 31
};

#define COLOR_TRANSPARENT 0xFF // 255

#define COLOR_VGA_BG 18
#define COLOR_VGA_FG 90
#define COLOR_VGA_MISC 125
#define COLOR_VGA_RED 4
#define COLOR_VGA_GREEN 0x2
#define COLOR_VGA_PURPLE 0x3b
#define COLOR_VGA_YELLOW 0x44
#define COLOR_VGA_LIGHT_BLUE 0x36

// 0x49, 0x92, 0xdb
#define COLOR_GRAY_DARK 0x49
#define COLOR_GRAY_DEFAULT 0x92 //144
#define COLOR_GRAY_LIGHT 0xdb

#define COLOR_GRAY_0 73
#define COLOR_GRAY_1 73
#define COLOR_GRAY_2 73
#define COLOR_GRAY_3 114
#define COLOR_GRAY_4 114
#define COLOR_GRAY_5 114
#define COLOR_GRAY_6 73
#define COLOR_GRAY_7 73
#define COLOR_GRAY_8 73
#define COLOR_GRAY_9 73

#define COLOR_BLACK      0x00
#define COLOR_RED        0xE0
#define COLOR_GREEN      0x1C
#define COLOR_BLUE       0x03
#define COLOR_CYAN       0x1F
#define COLOR_MAGENTA    0xE3
#define COLOR_YELLOW     0xFC
#define COLOR_WHITE      0x0F

#define COLOR_ORANGE     0xFC
#define COLOR_PINK       0xFC
#define COLOR_PURPLE     0xE3
#define COLOR_TURQUOISE  0x1F
#define COLOR_LIME_GREEN 0x1C
#define COLOR_GOLD       0xFC
#define COLOR_SILVER     0x18
#define COLOR_BRONZE     0x30

// Bright colors
#define COLOR_BRIGHT_BLACK     0x08
#define COLOR_BRIGHT_RED       0x0F
#define COLOR_BRIGHT_GREEN     0x1F
#define COLOR_BRIGHT_YELLOW    0x3F
#define COLOR_BRIGHT_BLUE      0x9F
#define COLOR_BRIGHT_MAGENTA   0xBF
#define COLOR_BRIGHT_CYAN      0xDF
#define COLOR_BRIGHT_WHITE     0xFF

// Dark colors
#define COLOR_DARK_BLACK       0x00
#define COLOR_DARK_RED         0x01
#define COLOR_DARK_GREEN       0x02
#define COLOR_DARK_YELLOW      0x03
#define COLOR_DARK_BLUE        0x04
#define COLOR_DARK_MAGENTA     0x05
#define COLOR_DARK_CYAN        0x06
#define COLOR_DARK_WHITE       0x07

#define COLOR_DARK_YELLOw		0xb0
#define COLOR_LIGHT_YELLOw		0xb1

#define COLOR_BOX_BG 0x20 /* 0x24*/
#define COLOR_BOX_DARK_RED 0xc4
#define COLOR_BOX_DARK_GREEN 0x90
#define COLOR_BOX_DARK_YELLOW 0xd0
#define COLOR_BOX_DARK_BLUE 0x52
#define COLOR_BOX_DARK_PURPLE 0xae
#define COLOR_BOX_DARK_AQUA 0x71
#define COLOR_BOX_DARK_GRAY 0xb2

#define COLOR_BOX_LIGHT_GRAY 0x91
#define COLOR_BOX_LIGHT_RED 0xe8
#define COLOR_BOX_LIGHT_GREEN 0xb4
#define COLOR_BOX_LIGHT_YELLOW 0xf4
#define COLOR_BOX_LIGHT_BLUE 0x96
#define COLOR_BOX_LIGHT_PURPLE 0xd2
#define COLOR_BOX_LIGHT_AQUA 0x95
#define COLOR_BOX_LIGHT_FG 0xfb /* 0xdb */
#define COLOR_BOX_DARK_BG 0x04
#define COLOR_BOX_DARK_BG2 0x24
#define COLOR_BOX_DARK_BG3 0x49
#define COLOR_BOX_DARK_ORANGE 0xcc
#define COLOR_BOX_LIGHT_ORANGE 0xec



color_t rgb_to_vga(color_t c);
int rgb_init_color_table();



#endif /* D0F51827_3250_49B2_9614_254FFF11BBC3 */
