#include "memory/vmm.h"
#include "memory/pmm.h"
#include "memory/paging.h"

page_directory_t *g_current_directory = 0;

// Get entry from page table for a given virtual address
page_table_entry *vmm_get_page_table_entry(page_table_t *table, uint32_t v_addr)
{
	if (table != NULL)
		return (&table->entries[PAGE_TABLE_INDEX(v_addr)]);
	return (NULL);
}
EXPORT_SYMBOL(vmm_get_page_table_entry);

// Get entry from page directory for a given virtual address
page_directory_entry *vmm_get_page_directory_entry(page_directory_t *dir, uint32_t v_addr)
{
	if (dir != NULL)
		return (&dir->entries[PAGE_DIRECTORY_INDEX(v_addr)]);
	return (NULL);
}
EXPORT_SYMBOL(vmm_get_page_directory_entry);

// Return a page table entry for a given virtual address
page_table_entry *vmm_get_page(const uint32_t v_addr)
{
	page_directory_t	 *dir	= g_current_directory;
	page_directory_entry *entry	= &dir->entries[PAGE_DIRECTORY_INDEX(v_addr)];
	page_table_t		 *table	= (page_table_t*)PAGE_GET_PHYSICAL_ADDRESS(entry);
	page_table_entry	 *page	= &table->entries[PAGE_TABLE_INDEX(v_addr)];

	return (page);
}
EXPORT_SYMBOL(vmm_get_page);

void *vmm_alloc_page(page_table_entry *page)
{
	uint32_t *frame = pmm_alloc_frames(1);

	if (frame != NULL) {
		SET_FRAME(page, (uint32_t)frame);
		SET_ATTRIBUTE(page, PTE_PRESENT);
	}

	return (frame);
}
EXPORT_SYMBOL(vmm_alloc_page);

void vmm_free_page(page_table_entry *page)
{
	uint32_t *address = (uint32_t*)PAGE_GET_PHYSICAL_ADDRESS(page);

	if (address != NULL)
		pmm_free_frames(address, 1);
	CLEAR_ATTRIBUTE(page, PTE_PRESENT);
}
EXPORT_SYMBOL(vmm_free_page);

bool vmm_map_page(uint32_t *p_addr, uint32_t *v_addr)
{
	page_directory_t		*dir = g_current_directory;
	page_directory_entry	*entry = &dir->entries[PAGE_DIRECTORY_INDEX((uint32_t)v_addr)];

	if ((*entry & PTE_PRESENT) != PTE_PRESENT) {
		page_table_t *table = (page_table_t*)pmm_alloc_frames(1);
		if (table == NULL)
			return (false);

		bzero(table, sizeof(page_table_t));

		page_directory_entry *entry = &dir->entries[PAGE_DIRECTORY_INDEX((uint32_t)v_addr)];
		SET_ATTRIBUTE(entry, PDE_PRESENT | PDE_READ_WRITE);
		SET_FRAME(entry, (uint32_t)table);
	}

	page_table_t *table = (page_table_t *)PAGE_GET_PHYSICAL_ADDRESS(entry);
	page_table_entry *page = &table->entries[PAGE_TABLE_INDEX((uint32_t)v_addr)];

	SET_ATTRIBUTE(page, PTE_PRESENT);
	SET_FRAME(page, (uint32_t)p_addr);

	return (true);
}
EXPORT_SYMBOL(vmm_map_page);

// Unmap a page
void	vmm_unmap_page(uint32_t *v_addr)
{
	page_table_entry *page = vmm_get_page((uint32_t)v_addr);

	SET_FRAME(page, 0); // Set physical address to 0
	CLEAR_ATTRIBUTE(page, PTE_PRESENT); // Clear present flag
}
EXPORT_SYMBOL(vmm_unmap_page);

// Initialise the virtual memory manager
int	vmm_init(void)
{
	page_directory_t *directory = (page_directory_t*)pmm_alloc_frames(3);
	if (directory == NULL)
		return (ERR_OUT_OF_MEMORY);
	memset32(directory->entries, PDE_READ_WRITE, TABLES_PER_DIR);

	page_table_t *table = (page_table_t*)pmm_alloc_frames(1);
	if (table == NULL)
		return (ERR_OUT_OF_MEMORY);

	// Allocate a 3GB page table
	page_table_t *table3G = (page_table_t*)pmm_alloc_frames(1);
	if (table3G == NULL)
		return (ERR_OUT_OF_MEMORY);

	// Clear the page table
	bzero(table, sizeof(page_table_t));
	bzero(table3G, sizeof(page_table_t));

	// Identity map the first 4MB
	for (uint32_t i = 0, frame = 0x0, virt = 0x0; i < PAGE_PER_TABLE; ++i, frame += PAGE_SIZE, virt += PAGE_SIZE) {
		page_table_entry page = 0;
		SET_ATTRIBUTE(&page, PTE_PRESENT | PTE_READ_WRITE);
		SET_FRAME(&page, frame);

		// Add page to 3GB page table
		table3G->entries[PAGE_TABLE_INDEX(virt)] = page;
	}

	// Map kernel space to 3GB (Higher half kernel)
	for (uint32_t i = 0, frame = 0x100000, virt = 0xC0000000; i < PAGE_PER_TABLE; i++, frame += PAGE_SIZE, virt += PAGE_SIZE) {
		page_table_entry page = 0;
		SET_ATTRIBUTE(&page, PTE_PRESENT | PTE_READ_WRITE);
		SET_FRAME(&page, frame);

		// Add page to 3GB page table
		table->entries[PAGE_TABLE_INDEX(virt)] = page;
	}

	page_directory_entry *entry = &directory->entries[PAGE_DIRECTORY_INDEX(0xC0000000)];
	SET_ATTRIBUTE(entry, PDE_PRESENT | PDE_READ_WRITE);
	SET_FRAME(entry, (uint32_t)table);

	page_directory_entry *entry2 = &directory->entries[PAGE_DIRECTORY_INDEX(0x00000000)];
	SET_ATTRIBUTE(entry2, PDE_PRESENT | PDE_READ_WRITE);
	SET_FRAME(entry2, (uint32_t)table3G);

	switch_page_directory(directory);
	enable_paging();

	return (0);	
}
EXPORT_SYMBOL(vmm_init);
