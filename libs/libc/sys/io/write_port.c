#include <stdint.h>

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
///  write_port(0x3f8, 'A');
/// ```
void write_port(uint16_t port, uint8_t data)
{
	__asm__ volatile("outb %0, %1" : : "a" (data), "dN" (port));
}
