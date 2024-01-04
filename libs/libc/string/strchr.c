#include "libc.h"

/// Find the first occurrence of a character in a string
///
/// ## Parameters
///
/// - `s`: String to search.
/// - `c`: Character to search for.
///
/// ## Examples
///
/// ```
/// char str[50] = "Hello world";
/// char *p = strchr(str, 'w');
/// puts(p); // world
/// ```
///
/// ## Return
///
/// Pointer to the first occurrence of `c` in `s`, or NULL if not found.
///
/// ## Note
///
/// - The string must be null-terminated.
char *strchr(const char *s, int c)
{
	size_t	i;

	for (i = 0; s[i] != '\0'; ++i)
	{
		if (s[i] == c)
			return ((char*)(s + i));
	}
	if (s[i] == c)
		return ((char*)(s + i));
	return (NULL);
}
