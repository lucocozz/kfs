#include "driver/keyboard.h"

uint8_t	g_keyboard_states = 0;
key_t	g_keyboard_poll = {0};
uint8_t	g_keyboard_layout = 0;

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
	uint8_t mask = KEY_SHIFT_MASK | KEY_CAPSLOCK_MASK;

	code = NORMALIZE_SCANCODE(code);
	if ((g_keyboard_states & mask) == mask)
		key = SCANCODE_KEY(code);
	else if (g_keyboard_states & mask)
		key = SCANCODE_SHIFT_KEY(code);
	else
		key = SCANCODE_KEY(code);
	return (key);
}

static void __handle_states_keys(uint8_t code)
{
	uint8_t key = NORMALIZE_SCANCODE(code);

	if (key == LEFT_CTRL)
		g_keyboard_states ^= KEY_CTRL_MASK;
	else if (key == LEFT_SHIFT || key == RIGHT_SHIFT)
		g_keyboard_states ^= KEY_SHIFT_MASK;
	else if (key == LEFT_ALT)
		g_keyboard_states ^= KEY_ALT_MASK;
	else if (key == CAPS_LOCK && SCANCODE_IS_PRESSED(code))
		g_keyboard_states ^= KEY_CAPSLOCK_MASK;
}

void	isr_keyboard(registers_t regs, struct stack_state stack)
{
	UNUSED(regs); UNUSED(stack);
	uint8_t code = inb(KEYBOARD_PORT_DATA);

	if (__is_state_key(code))
		__handle_states_keys(code);
	else {
		key_t key = {
			.code = code,
			.ascii = __scancode_to_ascii(code),
			.state = g_keyboard_states,
			.is_pressed = SCANCODE_IS_PRESSED(code),
		};
		keyboard_set_keypoll(key);
	}
}
EXPORT_SYMBOL(isr_keyboard);

key_t	keyboard_get_keypoll(void)
{
	key_t key = {0};

	key = g_keyboard_poll;
	g_keyboard_poll = (key_t){0};
	return (key);
}
EXPORT_SYMBOL(keyboard_get_keypoll);

void	keyboard_set_keypoll(key_t key)
{
	g_keyboard_poll = key;
}
EXPORT_SYMBOL(keyboard_set_keypoll);
