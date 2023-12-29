#include "driver/tty.h"

uint8_t			g_tty_index = 0;
vga_terminal_t	g_tty[TTY_COUNT] = {0};
uint16_t		*g_vga_buffer = VGA_BUFFER_ADDRESS;

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

void	term_init()
{
	while (g_tty_index < TTY_COUNT)
	{
		g_tty[g_tty_index].color = vga_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
		term_clear();
		++g_tty_index;
	}
	g_tty_index = 0;
}

void	term_set_color(enum vga_color fg, enum vga_color bg)
{
	g_tty[g_tty_index].color = vga_color(fg, bg);
}

void	term_put_entry_at(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	g_vga_buffer[index] = vga_entry(c, color);
}

void	term_put_entry(char c, uint8_t color)
{
	term_put_entry_at(c, color, g_tty[g_tty_index].column, g_tty[g_tty_index].row);
}

void	term_goto(size_t x, size_t y)
{
	g_tty[g_tty_index].column = x;
	g_tty[g_tty_index].row = y;
}

void	term_scroll_up(void)
{
	memmove(g_vga_buffer, g_vga_buffer + VGA_WIDTH, (VGA_BUFFER_SIZE - VGA_WIDTH) * sizeof(uint16_t));
	for (size_t x = 0; x < VGA_WIDTH; ++x)
		term_put_entry_at(' ', g_tty[g_tty_index].color, x, VGA_HEIGHT - 1);
}

bool __special_char_handler(char c)
{
	switch (c)
	{
	case '\b':
		if (g_tty[g_tty_index].column == 0) {
			if (g_tty[g_tty_index].row == 0)
				return (true);
			term_goto(VGA_WIDTH - 1, g_tty[g_tty_index].row - 1);
		} else
			--g_tty[g_tty_index].column;
		term_put_entry(' ', g_tty[g_tty_index].color);
		return (true);

	case '\n':
		term_goto(0, g_tty[g_tty_index].row + 1);
		if (g_tty[g_tty_index].row == VGA_HEIGHT) {
			term_scroll_up();
			term_goto(0, VGA_HEIGHT - 1);
		}
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
		term_put_entry(data[i], g_tty[g_tty_index].color);
		++g_tty[g_tty_index].column;
		if (g_tty[g_tty_index].column == VGA_WIDTH) {
			term_goto(0, g_tty[g_tty_index].row + 1);
			if (g_tty[g_tty_index].row == VGA_HEIGHT) {
				term_scroll_up();
				term_goto(0, VGA_HEIGHT - 1);
			}
		}
	}
	set_vga_cursor(g_tty[g_tty_index].column, g_tty[g_tty_index].row);
}

void	term_putc(char c)
{
	term_write(&c, 1);
}

void	term_puts(const char *str)
{
	term_write(str, strlen(str));
}

bool	__special_key_handler(key_t key)
{
	if (key.code >= KEY_F1 && key.code <= KEY_F1 + TTY_COUNT - 1) {
		memcpy(g_tty[g_tty_index].buffer, g_vga_buffer, VGA_BUFFER_SIZE * sizeof(uint16_t));
		g_tty_index = key.code - KEY_F1;
		memcpy(g_vga_buffer, g_tty[g_tty_index].buffer, VGA_BUFFER_SIZE * sizeof(uint16_t));
		term_goto(g_tty[g_tty_index].column, g_tty[g_tty_index].row);
		set_vga_cursor(g_tty[g_tty_index].column, g_tty[g_tty_index].row);
		return (true);
	}

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

void	term_putkey(key_t key)
{
	if (key.is_pressed == false)
		return;
	if (__special_key_handler(key) == true)
		return;
	term_write((const char*)&key.ascii, 1);
}

void	term_put_from_keyqueue(void)
{
	key_t key = keyboard_get_keyqueue();
	if (key.code != 0)
		term_putkey(key);
}
