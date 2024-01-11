#ifndef KERNEL_SHELL_H
#define KERNEL_SHELL_H

#include <stdint.h>
#include <stddef.h>

#include "driver/tty.h"
#include "builtin.h"
#include "printk.h"
#include "symbol_table.h"

#define SHELL_BUFFER_SIZE 256

#define ASCII_ART ""

void	shell(void);

#endif
