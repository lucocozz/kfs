#include "kernel.h"

/// Set the cursor position in the VGA I/O port
///
/// ## Parameters
///
/// - `x`: X position of the cursor.
/// - `y`: Y position of the cursor.
///
/// ## Examples
///
/// ```
/// set_vga_cursor(0, 0);
/// ```
///
/// ## Note
///
/// - The cursor position is relative to the top left corner of the screen.
void set_vga_cursor(int x, int y)
{
	uint16_t pos = y * VGA_WIDTH + x;

	outb(VGA_CTRL_REGISTER, VGA_CURSOR_LOW_BYTE);
	outb(VGA_DATA_REGISTER, LOW_B8(pos));
	outb(VGA_CTRL_REGISTER, VGA_CURSOR_HIGH_BYTE);
	outb(VGA_DATA_REGISTER, HIGH_B8(pos));
}
EXPORT_SYMBOL(set_vga_cursor);

/// Get the cursor position in the VGA I/O port
///
/// ## Parameters
///
/// - `x`: Pointer to the X position of the cursor.
/// - `y`: Pointer to the Y position of the cursor.
///
/// ## Examples
///
/// ```
/// int x, y;
/// get_vga_cursor(&x, &y);
/// ```
///
/// ## Return
///
/// The cursor position is returned through the `x` and `y` pointers.
///
/// ## Note
///
/// - The cursor position is relative to the top left corner of the screen.
void get_vga_cursor(int *x, int *y)
{
	uint16_t pos = 0;

	outb(VGA_CTRL_REGISTER, VGA_CURSOR_LOW_BYTE);
	pos |= inb(VGA_DATA_REGISTER);
	outb(VGA_CTRL_REGISTER, VGA_CURSOR_HIGH_BYTE);
	pos |= ((uint16_t)inb(VGA_DATA_REGISTER)) << 8;

	*x = pos % VGA_WIDTH;
	*y = pos / VGA_WIDTH;
}
EXPORT_SYMBOL(get_vga_cursor);
