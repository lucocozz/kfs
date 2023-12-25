#include "kernel.h"

uint16_t	g_keyboard_handlers = 0;

static bool __is_state_key(uint8_t code)
{
	code = NORMALIZE_SCANCODE(code);

	if (code == LEFT_CTRL || code == LEFT_SHIFT || code == RIGHT_SHIFT || code == LEFT_ALT || code == CAPS_LOCK)
		return (true);
	return (false);
}

static uint8_t __scancode_to_ascii(uint8_t code)
{
	uint8_t key;

	code = NORMALIZE_SCANCODE(code);
	if (g_keyboard_handlers & HANDLER_KEY_SHIFT && g_keyboard_handlers & HANDLER_KEY_CAPSLOCK)
		key = SCANCODE_KEY(code);
	else if (g_keyboard_handlers & (HANDLER_KEY_SHIFT | HANDLER_KEY_CAPSLOCK))
		key = SCANCODE_SHIFT_KEY(code);
	else
		key = SCANCODE_KEY(code);
	return (key);
}

static void __handle_states_keys(uint8_t code)
{
	uint8_t key = NORMALIZE_SCANCODE(code);

	if (key == LEFT_CTRL)
		g_keyboard_handlers ^= HANDLER_KEY_CTRL;
	else if (key == LEFT_SHIFT || key == RIGHT_SHIFT)
		g_keyboard_handlers ^= HANDLER_KEY_SHIFT;
	else if (key == LEFT_ALT)
		g_keyboard_handlers ^= HANDLER_KEY_ALT;
	else if (key == CAPS_LOCK) {
		if (SCANCODE_IS_PRESSED(code))
			g_keyboard_handlers ^= HANDLER_KEY_CAPSLOCK;
	}
}

void	keyboard_handler(void)
{
	uint8_t code = read_port(KEYBOARD_PORT_DATA);

	if (__is_state_key(code))
		__handle_states_keys(code);
	else {
		uint8_t key = __scancode_to_ascii(code);
		if (SCANCODE_IS_PRESSED(code))
			term_putc(key);
	}
}
