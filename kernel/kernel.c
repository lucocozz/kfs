#include "kernel.h"

uint8_t				g_tty_index = 0;
vga_terminal_t		g_tty[TTY_COUNT] = {0};
// uint32_t			_kernel_end = KERNEL_START + 0x100000;
uint16_t			*g_vga_buffer = (uint16_t*)0xC03FF000; //VGA_BUFFER_ADDRESS;

static void	__init_kernel()
{
	gdt_init();
	interrupts_init();
	// paging_init();
	term_init();
}

void	kernel_main(uint32_t magic, multiboot_info_t *boot_info)
{
	(void)magic; (void)boot_info;
	__init_kernel();
	shell();
}
EXPORT_SYMBOL(kernel_main);
