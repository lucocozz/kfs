#include "ctype.h"

/// The strtoupper() function converts ASCII characters to uppercase in the string str.
///
/// ## Parameters
///
/// - `str`: The string to convert.
///
/// ## Examples
///
/// ```
/// char *str = "Hello World!";
/// strtoupper(str);
/// printf("%s\n", str); // HELLO WORLD!
/// ```
///
/// ## Return
///
/// The converted string.
///
/// ## Note
///
/// - The strtoupper() function does not detect errors.
char	*strtoupper(char *str)
{
	for (int i = 0; str[i]; i++)
		str[i] = toupper(str[i]);
	return (str);
}
