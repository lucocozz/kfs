#include "string.h"

/// Reverse string
///
/// ## Parameters
///
/// - `str`: String to reverse
///
/// ## Examples
///
/// ```
/// char str[] = "Hello World!";
/// strrev(str);
/// printf("%s", str); // !dlroW olleH
/// ```
///
/// ## Return
///
/// - `str`: Reversed string
char *strrev(char *str)
{
	char	tmp;
	int		i = 0;
	int		j = strlen(str) - 1;

	while (i < j)
	{
		tmp = str[i];
		str[i++] = str[j];
		str[j--] = tmp;
	}
	return (str);
}
