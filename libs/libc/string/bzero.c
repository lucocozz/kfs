#include "libc.h"

/// Fill memory with zeros
///
/// ## Parameters
///
/// - `s`: Pointer to the block of memory to fill.
/// - `n`: Number of bytes to be set to zero.
///
/// ## Examples
///
/// ```
/// char str[] = "Hello world";
/// bzero(str, 6);
/// puts(str); // world
/// ```
/// ## Note
///
/// - The size of `s` must be at least `n` bytes.
void	bzero(void *s, size_t n)
{
	memset(s, 0, n);
}
