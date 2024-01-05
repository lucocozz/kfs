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
}

void	kernel_main()
{
	__init_kernel();
	term_clear();
	term_set_color(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK);
	term_puts("Hello,");
	term_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
	term_puts(" World!\n");
	term_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	printk("printk test: %d, %i, %s, %c, %x, %X, %p, %u\n", 65, 31, "This is a kernel", 'c', 42, 42, 0x42, 42);
	while (1)
		term_put_from_keyqueue();
}
