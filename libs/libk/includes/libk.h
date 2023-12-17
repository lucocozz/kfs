#ifndef LIBK_H
#define LIBK_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "tty.h"
#include "vga.h"
#include "interrupts.h"
#include "keyboard.h"

#define LOW_B16(address) (uint16_t)((address) & 0xFFFF)
#define HIGH_B16(address) (uint16_t)(((address) >> 16) & 0xFFFF)
#define LOW_B8(address) (uint8_t)((address) & 0xFF)
#define HIGH_B8(address) (uint8_t)(((address) >> 8) & 0xFF)

#endif
