#include "string.h"

/// The utoa() function converts the unsigned integer n to a string representation.
///
/// ## Parameters
///
/// - `n`: The unsigned integer to convert.
/// - `buffer`: The buffer to store the result.
/// - `radix`: The radix to use.
///
/// ## Examples
///
/// ```
/// char buffer[10];
/// utoa(42, buffer, 10);
/// printf("%s\n", buffer); // 42
///
/// utoa(42, buffer, 2);
/// printf("%s\n", buffer); // 101010
///
/// utoa(42, buffer, 16);
/// printf("%s\n", buffer); // 2A
/// ```
///
/// ## Return
///
/// The converted value.
///
/// ## Note
///
/// - The utoa() function does not detect errors.
/// - If you pass a radix that is not between 2 and 36, it will return NULL.
char *utoa(unsigned int n, char *buffer, int radix)
{
	int i = 0;

	if (radix < 2 || radix > 36)
		return (NULL);
	do {
		buffer[i++] = "0123456789abcdefghijklmnopqrstuvwxyz"[n % radix];
	} while ((n /= radix) > 0);
	buffer[i] = '\0';
	return (strrev(buffer));
}
