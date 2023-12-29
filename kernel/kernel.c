#include "kernel.h"

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
	term_puts("Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag\n");
	while (1)
		term_put_from_keyqueue();
}
