#include "driver/tty.h"

static void	__handle_backspace(void)
{
	size_t index;
	size_t len = 0;
	
	if (term_cursor_backward() == false)
		return;
	index = term_get_index();
	while (g_vga_buffer[index + len] != '\0')
		++len;
	memmove(g_vga_buffer + index, g_vga_buffer + index + 1, len);
	g_vga_buffer[index + len] = '\0';
}
EXPORT_SYMBOL(__handle_backspace);

static void	__handle_newline(void)
{
	term_goto(0, g_tty[g_tty_index].row + 1);
	if (g_tty[g_tty_index].row == VGA_HEIGHT) {
		term_scroll_up();
		term_goto(0, VGA_HEIGHT - 1);
	}
}
EXPORT_SYMBOL(__handle_newline);

static bool __special_char_handler(char c)
{
	switch (c)
	{
	case '\b':
		__handle_backspace();
		return (true);
	case '\n':
		__handle_newline();
		return (true);
	case '\t':
		if (term_get_c_entry_at() == '\0')
			term_puts("    ");
		return (true);
	default:
		return (false);
	}
}
EXPORT_SYMBOL(__special_char_handler);

void	term_write(const char *data, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		if (__special_char_handler(data[i]) == true)
			continue;
		term_put_c_entry(data[i]);
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
EXPORT_SYMBOL(term_write);
