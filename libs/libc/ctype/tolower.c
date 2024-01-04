#include <stdbool.h>
#include "ctype.h"

/// Converts the given character to lowercase.
int tolower(int c)
{
	if (isupper(c) == true)
		return (c + 32);
	return (c);
}
