#include "kernel.h"

uint8_t				g_tty_index = 0;
vga_terminal_t		g_tty[TTY_COUNT] = {0};
uint16_t			*g_vga_buffer = VGA_BUFFER_ADDRESS;
keyboard_queue_t	g_keyboard_queue = {0};

static void	__init_kernel(void)
{
	term_init();
	term_puts("Terminal initialized\n");
	term_puts("Initializing interrupts...\n");
	interrupts_init();
	term_puts("Interrupts initialized\n");
	term_puts("Initializing GDT...\n");
	gdt_init();
	term_puts("GDT initialized\n");
}

void	kernel_main()
{
	__init_kernel();
	// term_clear();
	shell();
}
EXPORT_SYMBOL(kernel_main);
