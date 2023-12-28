#include "driver/tty.h"

void	term_clear(void)
{
	uint8_t color = vga_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	for (size_t y = 0; y < VGA_HEIGHT; ++y) {
		for (size_t x = 0; x < VGA_WIDTH; ++x)
			term_put_entry_at(' ', color, x, y);
	}
	set_vga_cursor(0, 0);
	term_goto(0, 0);
}

void	term_init(void)
{
	g_term.buffer = VGA_BUFFER_ADDRESS;
	g_term.color = vga_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	term_clear();
}

void	term_set_color(enum vga_color fg, enum vga_color bg)
{
	g_term.color = vga_color(fg, bg);
}

void	term_put_entry_at(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	g_term.buffer[index] = vga_entry(c, color);
}

void	term_put_entry(char c, uint8_t color)
{
	term_put_entry_at(c, color, g_term.column, g_term.row);
}

void	term_goto(size_t x, size_t y)
{
	g_term.column = x;
	g_term.row = y;
}

bool __special_char_handler(char c)
{
	switch (c)
	{
	case '\b':
		if (g_term.column == 0) {
			if (g_term.row == 0)
				return (true);
			term_goto(VGA_WIDTH - 1, g_term.row - 1);
		} else
			--g_term.column;
		term_put_entry(' ', g_term.color);
		return (true);

	case '\n':
		term_goto(0, g_term.row + 1);
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
		if (__special_char_handler(data[i]) == true)
			continue;
		term_put_entry(data[i], g_term.color);
		++g_term.column;
		if (g_term.column == VGA_WIDTH) {
			term_goto(0, g_term.row + 1);
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


bool	__special_key_handler(keypress_t key)
{
	switch (key.code)
	{
	case KEY_ARROW_UP:
		term_puts("UP");
		return (true);
	case KEY_ARROW_DOWN:
		term_puts("DOWN");
		return (true);
	case KEY_ARROW_LEFT:
		term_puts("LEFT");
		return (true);
	case KEY_ARROW_RIGHT:
		term_puts("RIGHT");
		return (true);
	default:
		return (false);
	}
}

void	term_putkey(keypress_t key)
{
	if (__special_key_handler(key) == true)
		return;
	if (key.is_pressed == false)
		return;
	term_write((const char*)&key.ascii, 1);
}

void	term_putkey_from_queue(void)
{
	keypress_t key = keyboard_get_key();
	if (key.code != 0)
		term_putkey(key);
}