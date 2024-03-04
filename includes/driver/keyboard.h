// https://github.com/Stichting-MINIX-Research-Foundation/minix/blob/master/minix/drivers/tty/tty/keymaps/french.src

#ifndef KERNEL_DRIVER_KEYBOARD_H
#define KERNEL_DRIVER_KEYBOARD_H

#include <stdint.h>
#include "symbol_table.h"
#include "interrupt/interrupts.h"

#define KEYBOARD_QUEUE_CAPACITY 1024

#define LEFT_CTRL			0x1D
#define LEFT_CTRL_PRESSED	0x1D
#define LEFT_CTRL_RELEASED	0x9D

#define LEFT_SHIFT			0x2A
#define LEFT_SHIFT_PRESSED	0x2A
#define LEFT_SHIFT_RELEASED	0xAA

#define RIGHT_SHIFT				0x36
#define RIGHT_SHIFT_PRESSED		0x36
#define RIGHT_SHIFT_RELEASED	0xB6

#define CAPS_LOCK			0x3A
#define CAPS_LOCK_PRESSED	0x3A
#define CAPS_LOCK_RELEASED	0xBA

#define LEFT_ALT			0x38
#define LEFT_ALT_PRESSED	0x38
#define LEFT_ALT_RELEASED	0xB8


#define KEY_CTRL_MASK		0x1
#define KEY_SHIFT_MASK		0x2
#define KEY_ALT_MASK		0x4
#define KEY_CAPSLOCK_MASK	0x8

#define SCANCODE_KEY(code) (scancode_key_us_qwerty[code])
#define SCANCODE_SHIFT_KEY(code) (scancode_shift_key_us_qwerty[code])
#define SCANCODE_IS_PRESSED(code) (code <= 0x58)
#define SCANCODE_IS_UNPRESSED(code) (!(SCANCODE_IS_PRESSED(code)))
#define NORMALIZE_SCANCODE(code) (SCANCODE_IS_PRESSED(code) ? code : (code - 0x80))

#define KEY_ARROW_UP	0x48
#define KEY_ARROW_DOWN	0x50
#define KEY_ARROW_LEFT	0x4B
#define KEY_ARROW_RIGHT	0x4D
#define KEY_BACKSPACE	0x0E
#define KEY_ENTER		0x1C
#define KEY_TAB			0x0F

#define KEY_F1	0x3B
#define KEY_F2	0x3C
#define KEY_F3	0x3D
#define KEY_F4	0x3E
#define KEY_F5	0x3F
#define KEY_F6	0x40
#define KEY_F7	0x41
#define KEY_F8	0x42
#define KEY_F9	0x43
#define KEY_F10	0x44
#define KEY_F11	0x57
#define KEY_F12	0x58

static const uint8_t scancode_key_us_qwerty[] = {
	[0x01] =  27,  [0x02] = '1',  [0x03] = '2',  [0x04] = '3',  [0x05] = '4',
	[0x06] = '5',  [0x07] = '6',  [0x08] = '7',  [0x09] = '8',  [0x0A] = '9',
	[0x0B] = '0',  [0x0C] = '-',  [0x0D] = '=',  [0x0E] = '\b', [0x0F] = '\t',
	[0x10] = 'q',  [0x11] = 'w',  [0x12] = 'e',  [0x13] = 'r',  [0x14] = 't',
	[0x15] = 'y',  [0x16] = 'u',  [0x17] = 'i',  [0x18] = 'o',  [0x19] = 'p',
	[0x1A] = '[',  [0x1B] = ']',  [0x1C] = '\n', [0x1D] =  0,   [0x1E] = 'a',
	[0x1F] = 's',  [0x20] = 'd',  [0x21] = 'f',  [0x22] = 'g',  [0x23] = 'h',
	[0x24] = 'j',  [0x25] = 'k',  [0x26] = 'l',  [0x27] = ';',  [0x28] = '\'',
	[0x29] = '`',  [0x2A] =  0,   [0x2B] = '\\', [0x2C] = 'z',  [0x2D] = 'x',
	[0x2E] = 'c',  [0x2F] = 'v',  [0x30] = 'b',  [0x31] = 'n',  [0x32] = 'm',
	[0x33] = ',',  [0x34] = '.',  [0x35] = '/',  [0x36] =  0,   [0x37] = '*',
	[0x38] =  0,   [0x39] = ' ',
};

static const uint8_t scancode_shift_key_us_qwerty[] = {
	[0x01] =  27,  [0x02] = '!',  [0x03] = '@',  [0x04] = '#',  [0x05] = '$',
	[0x06] = '%',  [0x07] = '^',  [0x08] = '&',  [0x09] = '*',  [0x0A] = '(',
	[0x0B] = ')',  [0x0C] = '_',  [0x0D] = '+',  [0x0E] = '\b', [0x0F] = '\t',
	[0x10] = 'Q',  [0x11] = 'W',  [0x12] = 'E',  [0x13] = 'R',  [0x14] = 'T',
	[0x15] = 'Y',  [0x16] = 'U',  [0x17] = 'I',  [0x18] = 'O',  [0x19] = 'P',
	[0x1A] = '{',  [0x1B] = '}',  [0x1C] = '\n', [0x1D] =  0,   [0x1E] = 'A',
	[0x1F] = 'S',  [0x20] = 'D',  [0x21] = 'F',  [0x22] = 'G',  [0x23] = 'H',
	[0x24] = 'J',  [0x25] = 'K',  [0x26] = 'L',  [0x27] = ':',  [0x28] = '"',
	[0x29] = '~',  [0x2A] =  0,   [0x2B] = '|',  [0x2C] = 'Z',  [0x2D] = 'X',
	[0x2E] = 'C',  [0x2F] = 'V',  [0x30] = 'B',  [0x31] = 'N',  [0x32] = 'M',
	[0x33] = '<',  [0x34] = '>',  [0x35] = '?',  [0x36] =  0,   [0x37] = '*',
	[0x38] =  0,   [0x39] = ' ',
};

typedef struct key {
	uint8_t	code;
	uint8_t	ascii;
	uint8_t	is_pressed;
	uint8_t	state;
} key_t;

typedef struct {
	key_t		data[KEYBOARD_QUEUE_CAPACITY];
	uint32_t	size;
	uint32_t	readed;
} keyboard_queue_t;

typedef struct registers registers_t;
typedef struct stack_state stack_state_t;

extern uint8_t			g_keyboard_states;
extern keyboard_queue_t	g_keyboard_queue;

void	keyboard_handler(registers_t regs, stack_state_t stack);
key_t	keyboard_get_keyqueue(void);
void	keyboard_add_keyqueue(key_t key);

#endif
