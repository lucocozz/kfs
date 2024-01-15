#include "driver/tty.h"

void	term_cursor_forward(void)
{
	if (term_get_c_entry_at() != '\0')
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
EXPORT_SYMBOL(term_cursor_forward);
