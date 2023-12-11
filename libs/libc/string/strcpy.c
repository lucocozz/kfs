#include "libc.h"

/// Copy string src to dest.
///
/// ## Parameters
///
/// - `dest`: Destination string.
/// - `src`: Source string.
///
/// ## Examples
///
/// ```
/// char str[6];
/// strcpy(str, "Hello\n");
/// puts(str); // Hello
/// ```
///
/// ## Return
///
/// Pointer to dest.
///
/// ## Note
///
/// - `dest` must be large enough to contain the source string.
/// - The source and destination strings should not overlap.
/// - The terminating '\0' character is copied.
char	*strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; ++i)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
