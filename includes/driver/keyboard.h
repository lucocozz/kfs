#ifndef KERNEL_DRIVER_KEYBOARD_H
#define KERNEL_DRIVER_KEYBOARD_H

#include <stdint.h>

#define KEYBOARD_BUFFER_SIZE 2097152 // 2 MiB

extern char keyboard_buffer[KEYBOARD_BUFFER_SIZE];

#endif
