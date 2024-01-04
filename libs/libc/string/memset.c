#include "libc.h"

/// Fill memory with a constant byte
///
/// ## Parameters
///
/// - `s`: Pointer to the block of memory to fill.
/// - `c`: Value to be set. The value is passed as an int, but the function fills the block of memory using the unsigned char conversion of this value.
/// - `n`: Number of bytes to be set to the value.
///
/// ## Examples
///
/// ```
/// char str[] = "Hello world";
/// memset(str, '-', 6);
/// puts(str); // ------ world
/// ```
///
/// ## Return
///
/// A pointer to the memory area `s`.
///
/// ## Note
///
/// - The size of `s` must be at least `n` bytes.
void *memset(void *s, int c, size_t n)
{
	int8_t	*ptr = s;

	while (n--)
		*ptr++ = (int8_t)c;
	return (s);
}
