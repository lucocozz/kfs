#include "driver/tty.h"

static void	__handle_backspace(void)
{
	if (g_tty[g_tty_index].column == 0) {
		if (g_tty[g_tty_index].row == 0)
			return ;
		term_goto(VGA_WIDTH - 1, g_tty[g_tty_index].row - 1);
	} else
		--g_tty[g_tty_index].column;
	term_put_c_entry('\0');
	//TODO: handle backspace inner line
}

static void	__handle_newline(void)
{
	term_goto(0, g_tty[g_tty_index].row + 1);
	if (g_tty[g_tty_index].row == VGA_HEIGHT) {
		term_scroll_up();
		term_goto(0, VGA_HEIGHT - 1);
	}
}

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
		term_goto(g_tty[g_tty_index].column + 4, g_tty[g_tty_index].row);
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
