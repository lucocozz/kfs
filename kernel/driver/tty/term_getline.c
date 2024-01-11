#include "driver/tty.h"

static void	__read_input(void)
{
	while (true)
	{
		key_t key = keyboard_get_keyqueue();

		if (key.code == 0 || key.is_pressed == false)
			continue;
		if (key.ascii == '\n')
			break;

		term_putkey(key);
	}
}
EXPORT_SYMBOL(__read_input);

static void	__write_in_buffer(char *buffer, size_t size)
{
	size_t index = 0;
	size_t vga_index = term_get_index();

	while ((char)g_vga_buffer[vga_index] != '\0' && index < size)
	{
		buffer[index] = (char)g_vga_buffer[vga_index + index];
		++index;
	}
	buffer[index] = '\0';
}
EXPORT_SYMBOL(__write_in_buffer);

void	term_getline(char *buffer, size_t size)
{
	__read_input();
	term_go_home_line();
	__write_in_buffer(buffer, size);
	term_go_end_line();
	term_putc('\n');
}
EXPORT_SYMBOL(term_getline);
