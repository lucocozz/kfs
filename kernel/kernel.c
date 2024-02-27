#include "kernel.h"

uint8_t				g_tty_index = 0;
vga_terminal_t		g_tty[TTY_COUNT] = {0};
uint16_t			*g_vga_buffer = VGA_BUFFER_ADDRESS;

static void	__init_kernel()
{
	gdt_init();
	interrupts_init();
	term_init();
	// paging_init();
}

void init_memory(multiboot_info_t *boot_info)
{
	for (unsigned int i = 0; i < boot_info->mmap_length; i+= sizeof(struct multiboot_mmap_entry))
	{
		struct multiboot_mmap_entry *mmmt = (struct multiboot_mmap_entry*)(boot_info->mmap_addr + i);
		printk("Mmap entry: base_addr = 0x%08x%08x, length = 0x%08x%08x\n \tsize = 0x%x, type = 0x%x\n",
			(uint32_t)mmmt->addr_high, (uint32_t)mmmt->addr_low,
			(uint32_t)mmmt->len_high, (uint32_t)mmmt->len_low,
			(uint32_t)mmmt->size, (uint32_t)mmmt->type);
	}
}

void	kernel_main(uint32_t magic, multiboot_info_t *boot_info)
{
	// display boot info

	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
		return ;
	__init_kernel();
	init_memory(boot_info);
	for (;;);
	// shell();
}
EXPORT_SYMBOL(kernel_main);
