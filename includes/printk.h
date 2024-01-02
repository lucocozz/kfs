#ifndef KERNEL_PRINTK_H
#define KERNEL_PRINTK_H

#include <stdarg.h>
#include <stddef.h>

#include "driver/tty.h"
#include "string.h"
#include "stdlib.h"

#define PRINTK_BUFFER_CAPACITY 4096
#define PRINTK_FLAGS_INIT {0, 0, 0, ' ', '\0'}
#define PRINTK_BUFFER_INIT {0, 0, {0}}
#define PRINTK_FORMATS_TYPE "cspdiuxX%"

typedef struct printk_flags {
	int		padding;
	int		width;
	int		precision;
	char	fill;
	char	type;
} printk_flags_t;

typedef struct printk_buffer {
	int		i;
	int		len;
	char	data[PRINTK_BUFFER_CAPACITY];
} printk_buffer_t;

int				printk(const char *format, ...);
printk_flags_t	init_parse(void);
void			print_buffer();
void			insert_in_buffer(char c);
void			insert_str(printk_flags_t *flags, char *str);
void			insert_format(printk_flags_t *flags, char c);
void			format_c(va_list ap, printk_flags_t flags);
void			format_s(va_list ap, printk_flags_t flags);
void			format_p(va_list ap, printk_flags_t flags);
void			format_d(va_list ap, printk_flags_t flags);
void			format_i(va_list ap, printk_flags_t flags);
void			format_u(va_list ap, printk_flags_t flags);
void			format_x(va_list ap, printk_flags_t flags);
void			format_xu(va_list ap, printk_flags_t flags);
void			format_per(va_list ap, printk_flags_t flags);
int				parse_padding(char c, printk_flags_t *flags);
int				parse_fill(char c, printk_flags_t *flags);
int				parse_width(const char *s, printk_flags_t *flags, va_list ap);
int				parse_precision(const char *s, printk_flags_t *flags, va_list ap);

extern printk_buffer_t printk_buffer;

#endif
