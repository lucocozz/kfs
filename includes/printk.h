#ifndef KERNEL_PRINTK_H
#define KERNEL_PRINTK_H

#include <stdarg.h>
#include <stddef.h>

#include "driver/tty.h"
#include "string.h"
#include "stdlib.h"

#define KERN_EMERG		"<0>" /* system is unusable */
#define KERN_ALERT		"<1>" /* action must be taken immediately */
#define KERN_CRIT		"<2>" /* critical conditions */
#define KERN_ERR		"<3>" /* error conditions */
#define KERN_WARNING	"<4>" /* warning conditions */
#define KERN_NOTICE		"<5>" /* normal but significant condition */
#define KERN_INFO		"<6>" /* informational */
#define KERN_DEBUG		"<7>" /* debug-level messages */
#define KERN_DEFAULT	"<d>" /* default level */
#define KERN_CONT		"<c>" /* continuation of last printk() */

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

typedef struct g_printk_buffer {
	int		i;
	int		len;
	char	data[PRINTK_BUFFER_CAPACITY];
} printk_buffer_t;

int				printk(const char *format, ...);
void			printk_print_buffer(void);
void			printk_write(char c);
void			printk_puts(printk_flags_t *flags, char *str);
void			printk_putc(printk_flags_t *flags, char c);
void			printk_format_c(va_list ap, printk_flags_t flags);
void			printk_format_s(va_list ap, printk_flags_t flags);
void			printk_format_p(va_list ap, printk_flags_t flags);
void			printk_format_d(va_list ap, printk_flags_t flags);
void			printk_format_i(va_list ap, printk_flags_t flags);
void			printk_format_u(va_list ap, printk_flags_t flags);
void			printk_format_x(va_list ap, printk_flags_t flags);
void			printk_format_xu(va_list ap, printk_flags_t flags);
void			printk_format_per(va_list ap, printk_flags_t flags);
int				printk_parse_padding(char c, printk_flags_t *flags);
int				printk_parse_fill(char c, printk_flags_t *flags);
int				printk_parse_width(const char *s, printk_flags_t *flags, va_list ap);
int				printk_parse_precision(const char *s, printk_flags_t *flags, va_list ap);

extern printk_buffer_t g_printk_buffer;

#endif
