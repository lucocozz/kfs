#include <stdbool.h>

bool	startwith(const char *start_with, const char *str)
{
	int	i = 0;

	while (start_with[i] != '\0' && str[i] != '\0') {
		if (start_with[i] != str[i])
			return (false);
		++i;
	}
	return (start_with[i] == '\0' ? true : false);
}
