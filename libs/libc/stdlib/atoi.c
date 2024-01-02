#include "libc.h"

static int __skip_whitespace(const char *str)
{
	int i = 0;
	while (isspace(str[i]) == true)
		i++;
	return (i);
}


/// The atoi() function converts the initial portion
/// of the string pointed to by str to int representation.
///
/// ## Parameters
///
/// - `str`: The string to convert.
///
/// ## Examples
///
/// ```
/// int nb = atoi("42");
/// if (nb == 42)
/// 	printf("42 is the answer to life, the universe and everything.\n");
/// ```
///
/// ## Return
///
/// The converted value.
///
/// ## Note
///
/// - The atoi() function does not detect errors.
/// If you pass a string that is not a number, it will return 0.
int	atoi(const char *str)
{
	int	nb = 0;
	int	neg = 1;
	int	i = __skip_whitespace(str);

	if (str[i] == '-')
		neg *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (isdigit(str[i]) == true)
		nb = nb * 10 + (str[i++] - '0');
	return (nb * neg);
}
