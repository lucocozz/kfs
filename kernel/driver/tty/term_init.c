#include "driver/tty.h"

uint8_t				g_tty_index = 0;
vga_terminal_t		g_tty[TTY_COUNT] = {0};
uint16_t			*g_vga_buffer = VGA_BUFFER_ADDRESS;

static void	__write_prompt(char *str)
{
	for (size_t i = 0; str[i] != '\0'; ++i) {
		uint16_t entry = vga_entry(str[i], g_tty[g_tty_index].color);
		g_tty[g_tty_index].buffer[i] = entry;
	}
}

static void	__init_prompt(void)
{
	term_set_text_color(VGA_COLOR_GREEN);
	__write_prompt("$>");
	term_default_color();
	g_tty[g_tty_index].column = 3;
}

static void	__clear_buffer(uint16_t *buffer)
{
	uint16_t entry = vga_entry('\0', g_tty[g_tty_index].color);

	for (size_t i = 0; i < VGA_BUFFER_SIZE; ++i)
		buffer[i] = entry;
	term_goto(0, 0);
}

void	term_init()
{
	while (g_tty_index < TTY_COUNT)
	{
		term_default_color();
		if (g_tty_index == 0)
			__clear_buffer(g_vga_buffer);
		else {
			__clear_buffer(g_tty[g_tty_index].buffer);
			__init_prompt();
		}
		++g_tty_index;
	}
	g_tty_index = 0;
	set_vga_cursor(0, 0);
}
EXPORT_SYMBOL(term_init);
