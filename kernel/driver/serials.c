#include "driver/serials.h"

/// Read from a port (8 bits)
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

	ASM("inb %1, %0" : "=a" (result) : "dN" (port));
	return (result);
}
EXPORT_SYMBOL(inb);

/// Write to a port (8 bits)
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
	ASM("outb %0, %1" : : "a" (data), "dN" (port));
}
EXPORT_SYMBOL(outb);



/// Read from a port (16 bits)
///
/// ## Parameters
///
/// - `port`: Port to read from.
///
/// ## Examples
///
/// ```
/// uint16_t data = inw(0x3f8);
/// ```
///
/// ## Return
///
/// Data read from the port.
uint16_t inw(uint16_t port)
{
	uint16_t result;

	ASM("inw %1, %0" : "=a" (result) : "dN" (port));
	return (result);
}


/// Write to a port (16 bits)
///
/// ## Parameters
///
/// - `port`: Port to write to.
/// - `data`: Data to write.
///
/// ## Examples
///
/// ```
///  outw(0x3f8, 0x1234);
/// ```
void outw(uint16_t port, uint16_t data)
{
	ASM("outw %0, %1" : : "a" (data), "dN" (port));
}
