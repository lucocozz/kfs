#include "shell/shell.h"

static void	__helper(void)
{
	term_puts("Available commands:\n"
		" - reboot\n"
		" - halt\n"
		" - dump_stack\n"
		" - symtab\n"
		" - help\n"
		" - clear\n"
	);
}

static void	__prompt(void)
{
	term_set_text_color(VGA_COLOR_GREEN);
	term_puts("$>");
	term_default_color();
	g_tty[g_tty_index].column += 1;
	set_vga_cursor(g_tty[g_tty_index].column, g_tty[g_tty_index].row);
}

static void	__commands(char *input)
{
	if (strcmp(input, "") == 0)
		return ;
	else if (strcmp(input, "reboot") == 0)
		reboot();
	else if (strcmp(input, "halt") == 0)
		halt();
	else if (strcmp(input, "shutdown") == 0)
		shutdown();
	else if (strcmp(input, "dump_stack") == 0)
		dump_stack();
	else if (strcmp(input, "symtab") == 0)
		symbol_table_print();
	else if (strcmp(input, "help") == 0)
		__helper();
	else if (strcmp(input, "clear") == 0)
		term_clear();
	else if (strcmp(input, "art") == 0)
		term_puts(ASCII_ART);
	else
		printk("%s: command not found\n", input);
}

void	shell(void)
{
	char input[SHELL_BUFFER_SIZE];

	while (true) {
		__prompt();
		term_getline(input, SHELL_BUFFER_SIZE);
		__commands(input);
	}
}
EXPORT_SYMBOL(shell);
