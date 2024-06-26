#ifndef KERNEL_DRIVER_TTY_H
#define KERNEL_DRIVER_TTY_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "driver/vga.h"
#include "driver/keyboard.h"
#include "symbol_table.h"


#include "string.h"
#include "stdlib.h"

#define TTY_COUNT 4

typedef struct key key_t;

extern uint8_t			g_tty_index;
extern vga_terminal_t	g_tty[TTY_COUNT];

// VGA_TERMINAL
void	term_init(void);
void	term_clear(void);
void	term_set_color(enum vga_color fg, enum vga_color bg);
void	term_set_text_color(enum vga_color color);
void	term_default_color(void);
void	term_put_entry_at(char c, uint8_t color, size_t x, size_t y);
void	term_put_entry(char c, uint8_t color);
void	term_put_c_entry(char c);
void	term_put_c_entry_at(char c, size_t x, size_t y);
char	term_get_c_entry_at_pos(size_t x, size_t y);
char	term_get_c_entry_at(void);
void	term_goto(size_t x, size_t y);
void	term_write(const char *data, size_t size);
void	term_putc(char c);
void	term_putkey(key_t keypress);
void	term_put_from_keyqueue(void);
void	term_puts(const char *str);
void	term_scroll_up(void);
void	term_putnbr(int nb, int base);
size_t	term_get_index(void);
void	term_set_index(size_t index);
bool	term_cursor_backward(void);
void	term_cursor_forward(void);
void	term_getline(char *buffer, size_t size);
void	term_go_home_line(void);
void	term_go_end_line(void);

#endif
