#include <stdbool.h>
#include "ctype.h"

/// Converts the given character to uppercase.
int toupper(int c)
{
	if (islower(c) == true)
		return (c - 32);
	return (c);
}
