#include "libc.h"

/// Copy a string
///
/// ## Parameters
///
/// - `dest`: Destination string.
/// - `src`: Source string.
/// - `n`: Maximum number of characters to copy.
///
/// ## Examples
///
/// ```
/// char str[50] = "Hello";
/// strncpy(str, " world of code!", 5);
/// puts(str); // hello world
/// ```
///
/// ## Return
///
/// Pointer to dest.
///
/// ## Note
///
/// - The destination string must be large enough to contain the result.
/// - If the length of `src` is less than `n`, the remainder of `dest` will be
///   padded with null bytes.
/// - If the length of `src` is greater than or equal to `n`, the string will
///   not be null-terminated.
char *strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	for (i = 0; i < n && src[i] != '\0'; ++i)
		dest[i] = src[i];
	for (; i < n; ++i)
		dest[i] = '\0';
	return (dest);
}