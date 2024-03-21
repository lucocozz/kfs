#include "memory/kmalloc.h"

void	*kcalloc(size_t nmemb, size_t size)
{
	size_t	mem_size = nmemb * size;
	void	*ptr = kmalloc(mem_size);

	if (ptr == NULL)
		return (NULL);
	bzero(ptr, mem_size);
	return (ptr);
}
