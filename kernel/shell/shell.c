#include "shell/shell.h"
#include "memory/memory_map.h"

static void	__helper(void)
{
	term_puts("Available commands:\n"
		" - reboot\n"
		" - shutdown\n"
		" - halt\n"
		" - dump\n"
		" - symtab\n"
		" - mmap\n"
		" - help\n"
		" - clear\n"
		" - layout\n"
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
	else if (strcmp(input, "dump") == 0)
		dump_stack();
	else if (strcmp(input, "symtab") == 0)
		symbol_table_print();
	else if (strcmp(input, "mmap") == 0)
		memory_map_print();
	else if (strcmp(input, "help") == 0)
		__helper();
	else if (strcmp(input, "clear") == 0)
		term_clear();
	else if (strcmp(input, "art") == 0)
		term_puts(ASCII_ART);
	else if (startwith("layout", input) == true) {
		if (strlen(input) > strlen("layout") + 1)
			layout(&input[strlen("layout") + 1]);
		else
			printk("Valide layout:\n - US\n - FR\n");
	}
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
