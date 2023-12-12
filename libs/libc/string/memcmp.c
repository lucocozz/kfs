#include "libc.h"

/// Compare two blocks of memory
///
/// ## Parameters
///
/// - `s1`: Pointer to block of memory.
/// - `s2`: Pointer to block of memory.
/// - `n`: Number of bytes to compare.
///
/// ## Examples
///
/// ```
/// char str1[] = "Hello world";
/// char str2[] = "Hello worle";
/// printf("%d\n", memcmp("Hello world", str2, 11)); // 0
/// printf("%d\n", memcmp("Hello world", str3, 11)); // != 0
/// printf("%d\n", memcmp("Hello world", str3, 5)); // 0
/// ```
///
/// ## Return
///
/// An integer less than, equal to, or greater than zero if the first `n` bytes of `s1` is found, respectively, to be less than, to match, or be greater than the first `n` bytes of `s2`.
///
/// ## Note
///
/// - The size of `s1` and `s2` must be at least `n` bytes.
int memcmp(const void *s1, const void *s2, size_t n)
{
	const int8_t	*ptr1 = s1;
	const int8_t	*ptr2 = s2;

	while (n--)
	{
		if (*ptr1 != *ptr2)
			return (*ptr1 - *ptr2);
		++ptr1;
		++ptr2;
	}
	return (0);
}