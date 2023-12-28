#ifndef KERNEL_DRIVER_TTY_H
#define KERNEL_DRIVER_TTY_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "vga.h"
#include "keyboard.h"

#include "string.h"

typedef struct vga_terminal {
	size_t		row;
	size_t		column;
	uint8_t		color;
	uint16_t	*buffer;
} t_vga_terminal;

extern t_vga_terminal g_term;

// VGA_TERMINAL
void	term_init();
void	term_clear(void);
void	term_set_color(enum vga_color fg, enum vga_color bg);
void	term_put_entry_at(char c, uint8_t color, size_t x, size_t y);
void	term_put_entry(char c, uint8_t color);
void	term_goto(size_t x, size_t y);
void	term_write(const char *data, size_t size);
void	term_putc(char c);
void	term_putkey(keypress_t keypress);
void	term_putkey_from_queue(void);
void	term_puts(const char *str);

#endif
