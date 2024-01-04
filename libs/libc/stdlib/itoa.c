#include "string.h"

/// The itoa() function converts the integer n to a string representation.
///
/// ## Parameters
///
/// - `n`: The integer to convert.
/// - `buffer`: The buffer to store the result.
/// - `radix`: The radix to use.
///
/// ## Examples
///
/// ```
/// char buffer[10];
/// itoa(42, buffer, 10);
/// printf("%s\n", buffer); // 42
///
/// itoa(42, buffer, 2);
/// printf("%s\n", buffer); // 101010
///
/// itoa(42, buffer, 16);
/// printf("%s\n", buffer); // 2A
/// ```
///
/// ## Return
///
/// The converted value.
///
/// ## Note
///
/// - The itoa() function does not detect errors.
/// - If you pass a radix that is not between 2 and 36, it will return NULL.
char *itoa(int n, char *buffer, int radix)
{
	int i = 0;
	int sign = n;

	if (radix < 2 || radix > 36)
		return (NULL);
	if (sign < 0)
		n = -n;
	do {
		buffer[i++] = "0123456789abcdefghijklmnopqrstuvwxyz"[n % radix];
	} while ((n /= radix) > 0);
	if (sign < 0)
		buffer[i++] = '-';
	buffer[i] = '\0';
	return (strrev(buffer));	
}
