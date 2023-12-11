#include "libc.h"

/// Find the last occurrence of a character in a string
///
/// ## Parameters
///
/// - `s`: String to search.
/// - `c`: Character to search for.
///
/// ## Examples
///
/// ```
/// char str[50] = "Hello world wide web";
/// char *p = strrchr(str, 'w');
/// puts(p); // web
/// ```
///
/// ## Return
///
/// Pointer to the last occurrence of `c` in `s`, or NULL if not found.
///
/// ## Note
///
/// - The string must be null-terminated.
char *strrchr(const char *s, int c)
{
	for (size_t i = strlen(s); i > 0; --i)
	{
		if (s[i] == c)
			return ((char*)(s + i));
	}
	return (NULL);
}