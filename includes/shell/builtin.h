#ifndef KERNEL_BUILTIN_H
#define KERNEL_BUILTIN_H

#include "symbol_table.h"
#include "multiboot.h"

void	reboot(void);
void	halt(void);
void	shutdown(void);
void	dump_stack(void);
void	mmap_print(void);

extern multiboot_info_t	*g_boot_info;

#endif