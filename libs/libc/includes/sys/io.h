#ifndef LIBC_SYS_IO_H
#define LIBC_SYS_IO_H

#include <stdint.h>

uint8_t	read_port(uint16_t port);
void	write_port(uint16_t port, uint8_t data);

#endif
