#include "ctype.h"

/// The strtolower() function converts ASCII characters to lowercase in the string str.
///
/// ## Parameters
///
/// - `str`: The string to convert.
///
/// ## Examples
///
/// ```
/// char *str = "Hello World!";
/// strtolower(str);
/// printf("%s\n", str); // hello world!
/// ```
///
/// ## Return
///
/// The converted string.
///
/// ## Note
///
/// - The strtolower() function does not detect errors.
char	*strtolower(char *str)
{
	for (int i = 0; str[i]; i++)
		str[i] = tolower(str[i]);
	return (str);
}
