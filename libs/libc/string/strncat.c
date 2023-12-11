#include "libc.h"

/// Concatenate two strings
///
/// ## Parameters
///
/// - `dest`: Destination string.
/// - `src`: Source string.
/// - `n`: Maximum number of characters to concatenate.
///
/// ## Examples
///
/// ```
/// char str[50] = "Hello";
/// strncat(str, " world of code!", 5);
/// puts(str); // Hello world
/// ```
///
/// ## Return
///
/// Pointer to the destination string.
///
/// ## Note
///
/// - The destination string must be large enough to contain the result.
/// - The source string must be null-terminated.
char *strncat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	dest_len = strlen(dest);

	for (i = 0; src[i] != '\0' && i < n; ++i)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';
	return (dest);
}