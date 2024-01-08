#include "printk.h"

void	printk_print_buffer(void)
{
	term_write(g_printk_buffer.data, g_printk_buffer.i);
	g_printk_buffer.len += g_printk_buffer.i;
	g_printk_buffer.i = 0;
	g_printk_buffer.data[0] = '\0';
}

void	printk_write(const char *str, size_t len)
{
	for (size_t i = 0; str[i] != '\0' && i < len; ++i)
	{
		g_printk_buffer.data[g_printk_buffer.i++] = str[i];
		if (g_printk_buffer.i == PRINTK_BUFFER_CAPACITY - 1)
			printk_print_buffer();
	}
}

void	printk_putc(printk_flags_t *flags, char c)
{
	printk_write(&c, 1);
	if (flags->width > 0)
		flags->width--;
}

void	printk_puts(printk_flags_t *flags, char *str)
{
	for (int i = 0; str[i] != '\0'; i++) 
		printk_putc(flags, str[i]);
}
