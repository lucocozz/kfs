#include "libc.h"

/// Compare two strings.
///
/// ## Parameters
///
/// - `s1`: First string.
/// - `s2`: Second string.
///
/// ## Examples
///
/// ```
///  if (strcmp("Hello", "Hello") == 0)
///  	puts("Is equal\n");
/// ```
///
/// ## Return
///
/// - Zero if `s1` is equal to `s2`.
/// - Negative value if `s1` is less than `s2`.
/// - Positive value if `s1` is greater than `s2`.
int strcmp(const char *s1, const char *s2)
{
	size_t i = 0;

	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		++i;
	return (s1[i] - s2[i]);
}
