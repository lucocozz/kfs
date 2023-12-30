#include "driver/tty.h"

static void	__handle_function_key(key_t key)
{
	if (key.code < KEY_F1 + TTY_COUNT) {
		memcpy(g_tty[g_tty_index].buffer, g_vga_buffer, sizeof(uint16_t) * VGA_BUFFER_SIZE);
		g_tty_index = key.code - KEY_F1;
		memcpy(g_vga_buffer, g_tty[g_tty_index].buffer, sizeof(uint16_t) * VGA_BUFFER_SIZE);
		term_goto(g_tty[g_tty_index].column, g_tty[g_tty_index].row);
		set_vga_cursor(g_tty[g_tty_index].column, g_tty[g_tty_index].row);
	}
}

static void	__handle_key_arrow_left(void)
{
	if (g_tty[g_tty_index].column == 0) {
		if (g_tty[g_tty_index].row == 0)
			return ;
		term_goto(VGA_WIDTH - 1, g_tty[g_tty_index].row - 1);
		while (term_get_c_entry_at(g_tty[g_tty_index].column - 1, g_tty[g_tty_index].row) == '\0') {
			term_goto(g_tty[g_tty_index].column - 1, g_tty[g_tty_index].row);
			if (g_tty[g_tty_index].column == 0)
				break;
		}
	} else
		--g_tty[g_tty_index].column;
	set_vga_cursor(g_tty[g_tty_index].column, g_tty[g_tty_index].row);
}

static void	__handle_key_arrow_right(void)
{
	if (term_get_c_entry_at(g_tty[g_tty_index].column, g_tty[g_tty_index].row) != '\0')
		term_goto(g_tty[g_tty_index].column + 1, g_tty[g_tty_index].row);
	if (g_tty[g_tty_index].column == VGA_WIDTH) {
		term_goto(0, g_tty[g_tty_index].row + 1);
		if (g_tty[g_tty_index].row == VGA_HEIGHT) {
			term_scroll_up();
			term_goto(0, VGA_HEIGHT - 1);
		}
	}
	set_vga_cursor(g_tty[g_tty_index].column, g_tty[g_tty_index].row);
}

static bool	__handle_arrow_key(key_t key)
{
	switch (key.code)
	{
	case KEY_ARROW_UP:
		return (true);
	case KEY_ARROW_DOWN:
		return (true);
	case KEY_ARROW_LEFT:
		__handle_key_arrow_left();
		return (true);
	case KEY_ARROW_RIGHT:
		__handle_key_arrow_right();
		return (true);
	default:
		return (false);
	}
}

static bool	__special_key_handler(key_t key)
{
	if (key.code >= KEY_F1 && key.code <= KEY_F10) {
		__handle_function_key(key);
		return (true);
	}
	return (__handle_arrow_key(key));
}

void	term_putkey(key_t key)
{
	if (key.is_pressed == false)
		return;
	if (__special_key_handler(key) == true)
		return;
	term_putc(key.ascii);
}
