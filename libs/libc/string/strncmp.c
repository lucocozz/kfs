#include "libc.h"

/// Compare two strings
///
/// ## Parameters
///
/// - `s1`: First string.
/// - `s2`: Second string.
/// - `n`: Maximum number of characters to compare.
///
/// ## Examples
///
/// ```
///  if (strncmp("Hello", "Hello world", 5) == 0)
///  	puts("Is equal\n");
/// ```
///
/// ## Return
///
/// - Zero if `s1` is equal to `s2`.
/// - Negative value if `s1` is less than `s2`.
/// - Positive value if `s1` is greater than `s2`.
///
/// ## Note
///
/// - The comparison stops after `n` characters or when a '\0' is reached.
int strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i = 0;

	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < n)
		++i;
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}