#include "ctype.h"

/// Checks if the given character is alphanumeric.
int isalnum(int c)
{
	return (isalpha(c) || isdigit(c));
}
