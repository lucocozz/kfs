#include "libc.h"

/// Get the length of a string
///
/// ## Parameters
///
/// - `str`: String.
///
/// ## Examples
///
/// ```
/// printf("%d\n", strlen("Hello")); // 5
/// ```
///
/// ## Return
///
/// Length of the string.
size_t strlen(const char *str)
{
	size_t	i = 0;

	while (str[i] != '\0')
		++i;
	return (i);
}
