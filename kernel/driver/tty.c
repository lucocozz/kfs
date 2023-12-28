#include "driver/tty.h"

void	term_clear(void)
{
	uint8_t color = vga_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	for (size_t y = 0; y < VGA_HEIGHT; ++y) {
		for (size_t x = 0; x < VGA_WIDTH; ++x)
			term_put_entry_at(' ', color, x, y);
	}
	set_vga_cursor(0, 0);
	g_term.column = 0;
	g_term.row = 0;
}

void	term_init(void)
{
	g_term.buffer = VGA_BUFFER_ADDRESS;
	g_term.color = vga_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	term_clear();
}

void	term_set_color(uint8_t color)
{
	g_term.color = color;
}

void	term_put_entry_at(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	g_term.buffer[index] = vga_entry(c, color);
}

bool __special_key_handler(char c)
{
	switch (c)
	{
	case '\b':
		if (g_term.column == 0) {
			if (g_term.row == 0)
				return (true);
			g_term.column = VGA_WIDTH - 1;
			--g_term.row;
		} else 
			--g_term.column;
		term_put_entry_at(' ', g_term.color, g_term.column, g_term.row);
		return (true);

	case '\n':
		g_term.column = 0;
		++g_term.row;
		if (g_term.row == VGA_HEIGHT)
			g_term.row = 0;
		return (true);

	default:
		return (false);
	}
}

void	term_write(const char *data, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		if (__special_key_handler(data[i]) == true)
			continue;
		term_put_entry_at(data[i], g_term.color, g_term.column, g_term.row);
		++g_term.column;
		if (g_term.column == VGA_WIDTH) {
			g_term.column = 0;
			++g_term.row;
			if (g_term.row == VGA_HEIGHT)
				g_term.row = 0;
		}
	}
	set_vga_cursor(g_term.column, g_term.row);
}

void	term_putc(char c)
{
	term_write(&c, 1);
}

void	term_puts(const char *str)
{
	term_write(str, strlen(str));
}
