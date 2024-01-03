#ifndef LIBC_STDLIB_H
#define LIBC_STDLIB_H

#include <stddef.h>

int		atoi(const char *str);
char	*itoa(int n, char *buffer, int radix);
char	*utoa(unsigned int n, char *buffer, int radix);

#endif
