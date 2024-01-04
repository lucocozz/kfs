#include "libc.h"

/// Concatenate two strings
///
/// ## Parameters
///
/// - `dest`: Destination string.
/// - `src`: Source string.
///
/// ## Examples
///
/// ```
/// char str[50] = "Hello";
/// strcat(str, " world");
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
char *strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	dest_len = strlen(dest);

	for (i = 0; src[i] != '\0'; ++i)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';
	return (dest);
}
