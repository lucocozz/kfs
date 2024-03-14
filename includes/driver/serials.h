#ifndef KERNEL_DRIVER_SERIALS_H
#define KERNEL_DRIVER_SERIALS_H

#include <stdint.h>
#include "system/utils.h"
#include "symbol_table.h"

#define KEYBOARD_PORT_DATA 0x60
#define KEYBOARD_PORT_STATUS 0x64

uint8_t		inb(uint16_t port);
void		outb(uint16_t port, uint8_t data);
uint16_t	inw(uint16_t port);
void		outw(uint16_t port, uint16_t data);

#endif
