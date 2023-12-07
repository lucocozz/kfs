#include "kernel.h"

static size_t	__strlen(const char *str)
{
	size_t	i = 0;

	while (str[i] != '\0')
		++i;
	return (i);
}

inline uint8_t	vga_color(enum vga_color fg, enum vga_color bg)
{
	return (fg | bg << 4);
}

static inline uint16_t	__vga_entry(unsigned char uc, uint8_t color)
{
	return ((uint16_t)uc | (uint16_t)color << 8);
}

void	term_init()
{
	g_term.color = vga_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	for (size_t y = 0; y < VGA_HEIGHT; ++y) {
		for (size_t x = 0; x < VGA_WIDTH; ++x)
			term_put_entry_at(' ', g_term.color, x, y);
	}
}

void	term_set_color(uint8_t color)
{
	g_term.color = color;
}

void	term_put_entry_at(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	g_term.buffer[index] = __vga_entry(c, color);
}


void	term_write(const char *data, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		term_put_entry_at(data[i], g_term.color, g_term.column, g_term.row);
		++g_term.column;
		if (g_term.column == VGA_WIDTH) {
			g_term.column = 0;
			++g_term.row;
			if (g_term.row == VGA_HEIGHT)
				g_term.row = 0;
		}
	}
}

void	term_putc(char c)
{
	term_write(&c, 1);
}

void	term_puts(const char *str)
{
	term_write(str, __strlen(str));
}
