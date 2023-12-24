#include <stdbool.h>
#include "ctype.h"

int toupper(int c)
{
	if (islower(c) == true)
		return (c - 32);
	return (c);
}
