#include "driver/ports.h"

/// Read from a port
///
/// ## Parameters
///
/// - `port`: Port to read from.
///
/// ## Examples
///
/// ```
/// uint8_t data = inb(0x3f8);
/// ```
///
/// ## Return
///
/// Data read from the port.
uint8_t inb(uint16_t port)
{
	uint8_t result;

	__asm__ volatile("inb %1, %0" : "=a" (result) : "dN" (port));
	return (result);
}

/// Write to a port
///
/// ## Parameters
///
/// - `port`: Port to write to.
/// - `data`: Data to write.
///
/// ## Examples
///
/// ```
///  outb(0x3f8, 'A');
/// ```
void outb(uint16_t port, uint8_t data)
{
	__asm__ volatile("outb %0, %1" : : "a" (data), "dN" (port));
}
