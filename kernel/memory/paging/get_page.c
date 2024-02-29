#include "memory/memory.h"


static page_t	*__create_page(uint32_t address, page_directory_t *directory)
{
	uint32_t physical_address;
	uint32_t table_index = PAGE_TABLE_INDEX(address);
	uint32_t page_index = PAGE_INDEX(address);

	directory->tables.virtual[table_index] = (page_table_t*)kmalloc_ap(sizeof(page_table_t), &physical_address);
	// bzero(directory->tables.virtual[table_index]->pages, sizeof(page_table_t));
	directory->tables.physical[table_index] = physical_address | PAGE_FLAG_PRESENT | PAGE_FLAG_WRITE | PAGE_FLAG_USER;
	return (&directory->tables.virtual[table_index]->pages[page_index]);
}


page_t	*get_page(uint32_t address, page_directory_t *directory, bool make)
{
	uint32_t table_index = PAGE_TABLE_INDEX(address);
	uint32_t page_index = PAGE_INDEX(address);

	if (directory->tables.virtual[table_index] != NULL)
		return (&directory->tables.virtual[table_index]->pages[page_index]);
	else if (make == true)
		return (__create_page(address, directory));
	return (NULL);
}
EXPORT_SYMBOL(get_page);
