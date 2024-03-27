#include "memory/vmm.h"


int	munmap(void *addr, size_t size)
{
	UNUSED(size);
	UNUSED(addr);
	return (0);
}