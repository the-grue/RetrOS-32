/**
 * @file vbe.c
 * @author Joe Bayer (joexbayer)
 * @brief VESA / VBE code
 * @version 0.1
 * @date 2024-01-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <vbe.h>
#include <colors.h>
#include <libc.h>
#include <font8.h>
#include <args.h>

#include <arch/io.h>

static struct vbe_mode_info_structure __vbe_info;
struct vbe_mode_info_structure* vbe_info = &__vbe_info;

uint8_t cursor[16][16] = {
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,90,90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,90,90,90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,90,90,90,90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,90,90,90,90,90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,90,90,90,90,90,90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,90,90,90,90,90,90,90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,90,90,90,90,90,0x92,0x92,0x92,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,90,90,0x92,90,90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,90,0x92,0x00,90,90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,0x92,0x00,0x00,0x00,90,90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,0x00,0x00,0x00,0x00,90,90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,0x00,0x00,0x00,0x00,0x00,90,0x92,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,0x00,0x00,0x00,0x00,0x00,0x92,0x92,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
};

#define VESA_BG_COLOR COLOR_BOX_DARK_CYAN

#define PALETTE_MASK 0x3C6
#define PALETTE_READ 0x3C7
#define PALETTE_WRITE 0x3C8
#define PALETTE_DATA 0x3C9

#define VGA_INDEX_REGISTER 0x3C0
#define VGA_DATA_REGISTER 0x3C1
#define PALETTE_SIZE 768

static unsigned char originalPalette[PALETTE_SIZE];

void reset_vga_palette() {
    int i;
    
    // Initialize VGA adapter
    outportb(VGA_INDEX_REGISTER, 0x03C0);
    
    // Write original VGA palette values
    for (i = 0; i < PALETTE_SIZE; i++) {
        outportb(VGA_DATA_REGISTER, originalPalette[i]);
    }
}

void vga_set_palette()
{
    int i;
    outportb(VGA_INDEX_REGISTER, 0x03C0);
    for (i = 0; i < PALETTE_SIZE; i++) {
        originalPalette[i] = inportb(VGA_DATA_REGISTER);
    }

    /* Currently only supports EDIM1 (RRRGGGBB) palette. */
    outportb(PALETTE_MASK, 0xFF);
    outportb(PALETTE_WRITE, 0);
    for (uint8_t i = 0; i < 255; i++) {
        outportb(PALETTE_DATA, (((i >> 5) & 0x7) * (256 / 8)) / 4);
        outportb(PALETTE_DATA, (((i >> 2) & 0x7) * (256 / 8)) / 4);
        outportb(PALETTE_DATA, (((i >> 0) & 0x3) * (256 / 4)) / 4);
    }

    // set color 255 = white
    outportb(PALETTE_DATA, 0x3F);
    outportb(PALETTE_DATA, 0x3F);
    outportb(PALETTE_DATA, 0x3F);
    
}

/* http://www.piclist.com/tecHREF/datafile/charset/extractor/charset_extractor.html */

unsigned short b8to16(unsigned char c)
{
    return (((unsigned short)c)<<8 ) | c;
}

void vesa_put_pixel(uint8_t* buffer, int x,int y, unsigned char color)
{
    putpixel(buffer, x , y, color, vbe_info->pitch);
}

void vesa_put_block(uint8_t* buffer, unsigned char c, int x, int y, int color) 
{
    for (int l = 0; l < 8; l++) {
        for (int i = 8; i >= 0; i--) {
            if (font8x8_block[c][l] & (1 << i)) {
                putpixel(buffer, (x)+i,  (y)+l, color, vbe_info->pitch);
            }
        }
    }
}

void vesa_put_char(uint8_t* buffer, unsigned char c, int x, int y, int color) 
{
    for (int l = 0; l < 8; l++) {
        for (int i = 8; i >= 0; i--) {
            if (font8x8_basic[c][l] & (1 << i)) {
                putpixel(buffer, (x)+i,  (y)+l, color, vbe_info->pitch);
            }
        }
    }
}

void vesa_put_char16(uint8_t* buffer, unsigned char c, int x, int y, int color)
{
    for (int l = 0; l < 16; l++) {
        for (int i = 15; i >= 0; i--) {
            if (font8x8_basic[c][l/2] & (1 << (i/2))) {
                putpixel(buffer, (x)+i,  (y)+l, color, vbe_info->pitch);
            }
        }
    }
}

/*
    Possible icons colors prefix:
    18, 
*/

void vesa_put_icon16(uint8_t* buffer, int x, int y)
{
    for (int l = 0; l < 16; l++) {

        for (int i = 0; i < 16; i++) {
            if (cursor[l][i] != 0x0) {
                putpixel(buffer, (x)+i,  (y)+l, cursor[l][i], vbe_info->pitch);
            } else {
                //putpixel((x)+i,  (y)+l, VESA_BG_COLOR);
            }
        }
    }
}

void vesa_write(uint8_t* buffer, int x, int y, const char* data, int size, int color)
{
	for (int i = 0; i < size; i++)
		vesa_put_char(buffer, data[i], x+(i*PIXELS_PER_CHAR), y, color);
}

void vesa_write_str(uint8_t* buffer, int x, int y, const char* data, int color)
{
	vesa_write(buffer, x, y, data, strlen(data), color);
}

void vesa_inner_box(uint8_t* buffer, int x, int y, int w, int h, color_t color)
{
    vesa_fillrect(buffer, x, y, w, h, color);

    vesa_line_horizontal(buffer, x, y, w, 31);
    vesa_line_horizontal(buffer, x, y+h, w, COLOR_VGA_MEDIUM_DARK_GRAY+5);

    vesa_line_vertical(buffer, x, y, h, 31);
    vesa_line_vertical(buffer, x+w, y, h, COLOR_VGA_MEDIUM_DARK_GRAY+5);
}

void vesa_fill(uint8_t* buffer, unsigned char color)
{
    for (int i = 0; i < vbe_info->height; i++)
        for (int j = 0; j < vbe_info->width; j++)
            putpixel(buffer, j, i, color, vbe_info->pitch);
}

void vesa_fillrect(uint8_t* buffer, int x, int y, int w, int h, int color){
    int i, j;
    for (j = y; j < (y+h); j++)
        for (i = x; i < (x+w); i++)
            putpixel(buffer, i, j, color, vbe_info->pitch);
}

#define GFX_MAX_FMT_STR_SIZE 50

int vesa_printf(uint8_t* buffer, int32_t x, int32_t y, int color, char* fmt, ...)
{
	va_list args;

	int x_offset = 0;
	int written = 0;
	char str[GFX_MAX_FMT_STR_SIZE];
	int num = 0;

	va_start(args, fmt);

	while (*fmt != '\0') {
		switch (*fmt)
		{
			case '%':
				memset(str, 0, GFX_MAX_FMT_STR_SIZE);
				switch (*(fmt+1))
				{
					case 'd':
					case 'i': ;
						num = va_arg(args, int);
						itoa(num, str);
						vesa_write_str(buffer, x+(x_offset*PIXELS_PER_CHAR), y, str, color);
						x_offset += strlen(str);
						break;
                    case 'p': ; /* p for padded int */
						num = va_arg(args, int);
						itoa(num, str);
						vesa_write_str(buffer, x+(x_offset*PIXELS_PER_CHAR), y, str, color);
						x_offset += strlen(str);

                        if(strlen(str) < 3){
                            int pad = 3-strlen(str);
                            for (int i = 0; i < pad; i++){
                                vesa_put_char(buffer, ' ', x+(x_offset*PIXELS_PER_CHAR), y, color);
                                x_offset++;
                            }
                        }
						break;
					case 'x':
					case 'X': ;
						num = va_arg(args, int);
						itohex(num, str);
						vesa_write_str(buffer, x+(x_offset*PIXELS_PER_CHAR), y, str, color);
						x_offset += strlen(str);
						break;
					case 's': ;
						char* str_arg = va_arg(args, char *);
						vesa_write_str(buffer, x+(x_offset*PIXELS_PER_CHAR), y, str_arg, color);
						x_offset += strlen(str_arg);
						break;
					case 'c': ;
						char char_arg = (char)va_arg(args, int);
						vesa_put_char(buffer, char_arg, x+(x_offset*PIXELS_PER_CHAR), y, color);
						x_offset++;
						break;
					default:
                        break;
				}
				fmt++;
				break;
			case '\n':
				y += 8;
				written += x_offset;
				x_offset = 0;
				break;
			default:  
				vesa_put_char(buffer, *fmt, x+(x_offset*PIXELS_PER_CHAR), y, color);
				x_offset++;
                written++;
			}
        fmt++;
    }
	written += x_offset;
	return written;
}