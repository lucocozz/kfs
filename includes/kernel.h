#ifndef KERNEL_H
#define KERNEL_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __linux__
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
#ifndef __i386__
#error "This needs to be compiled with a ix86-elf compiler"
#endif

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

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

typedef struct vga_terminal {
	size_t		row;
	size_t		column;
	uint8_t		color;
	uint16_t	*buffer;
} t_vga_terminal;

extern t_vga_terminal g_term;

// VGA_TERMINAL
void	term_init();
void	term_set_color(uint8_t color);
void	term_put_entry_at(char c, uint8_t color, size_t x, size_t y);
void	term_write(const char *data, size_t size);
void	term_putc(char c);
void	term_puts(const char *str);
uint8_t	vga_color(enum vga_color fg, enum vga_color bg);


#endif
