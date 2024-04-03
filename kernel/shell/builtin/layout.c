#include "driver/keyboard.h"
#include "string.h"

void	layout(char *layout)
{
	static const char *layout_ids[MAX_LAYOUT] = {
		[LAYOUT_US] = "US",
		[LAYOUT_FR] = "FR",
	};

	layout = strtoupper(layout);

	for (uint8_t i = 0; i < MAX_LAYOUT; ++i) {
		if (strcmp(layout, layout_ids[i]) == 0) {
			g_keyboard_layout = i;
			return;
		}
	}
	printk("'%s' is invalide layout, choose between:\n", layout);
	for (uint8_t i = 0; i < MAX_LAYOUT; ++i)
		printk(" - %s\n", layout_ids[i]);
}
