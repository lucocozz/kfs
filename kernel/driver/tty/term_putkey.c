#include "driver/tty.h"
#include "printk.h"

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

static bool	__term_cursor_back(void)
{
	size_t index = term_get_index();

	if (index == 0 || (char)g_vga_buffer[index - 1] == '\0')
		return (false);
	term_set_index(index - 1);
	return (true);
}

static void	__term_cursor_front(void)
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

static void	__handle_key_backspace(void)
{
	size_t index;
	size_t len = 0;
	
	if (__term_cursor_back() == false)
		return;
	index = g_tty[g_tty_index].row * VGA_WIDTH + g_tty[g_tty_index].column;
	while (g_vga_buffer[index + len] != '\0')
		++len;
	memmove(g_vga_buffer + index, g_vga_buffer + index + 1, len);
	g_vga_buffer[index + len] = '\0';
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
		__term_cursor_back();
		return (true);
	case KEY_ARROW_RIGHT:
		__term_cursor_front();
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
	if (key.code == KEY_BACKSPACE) {
		__handle_key_backspace();
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
