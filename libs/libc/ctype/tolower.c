#include <stdbool.h>
#include "ctype.h"

int tolower(int c)
{
	if (isupper(c) == true)
		return (c + 32);
	return (c);
}
