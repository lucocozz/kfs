#ifndef KERNEL_DRIVER_VGA_H
#define KERNEL_DRIVER_VGA_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "sys/io.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_BUFFER_SIZE (VGA_WIDTH * VGA_HEIGHT);
/// VGA_CTRL_REGISTER is the address of the VGA control register.
#define VGA_CTRL_REGISTER 0x3D4
/// VGA_DATA_REGISTER is the address of the VGA data register.
#define VGA_DATA_REGISTER 0x3D5
/// VGA_CURSOR_HIGH_BYTE is the address of the VGA cursor high byte register.
#define VGA_CURSOR_HIGH_BYTE 0x0E
/// VGA_CURSOR_LOW_BYTE is the address of the VGA cursor low byte register.
#define VGA_CURSOR_LOW_BYTE 0x0F
#define VGA_BUFFER_ADDRESS (uint16_t *)0xB8000

/* Hardware text mode color constants. */
enum vga_color
{
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


static inline uint8_t	vga_color(enum vga_color fg, enum vga_color bg)
{
	return (fg | bg << 4);
}

static inline uint16_t	vga_entry(unsigned char uc, uint8_t color)
{
	return ((uint16_t)uc | (uint16_t)color << 8);
}

void	set_vga_cursor(int x, int y);
void	get_vga_cursor(int *x, int *y);

#endif
