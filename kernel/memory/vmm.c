#include "memory/vmm.h"
#include "memory/pmm.h"
#include "kernel.h"

page_directory_t *current_directory = 0;

// Get entry from page table for a given virtual address
page_table_entry *get_page_table_entry(page_table_t *table, virt_addr_t address) {
	if (table) {
		return &table->entries[PAGE_TABLE_INDEX(address)];
	}
	return 0;
}

// Get entry from page directory for a given virtual address
page_directory_entry *get_page_directory_entry(page_directory_t *dir, virt_addr_t address) {
	if (dir) {
		return &dir->entries[PAGE_DIRECTORY_INDEX(address)];
	}
	return 0;
}

// Return a page table entry for a given virtual address
page_table_entry *get_page(const virt_addr_t v_addr) {
	// get page directory
	page_directory_t *dir = current_directory;

	// get page table in directory
	page_directory_entry *entry = &dir->entries[PAGE_DIRECTORY_INDEX(v_addr)];
	page_table_t *table = (page_table_t *)PAGE_GET_PHYSICAL_ADDRESS(entry);

	// get page in table
	page_table_entry *page = &table->entries[PAGE_TABLE_INDEX(v_addr)];

	// return page
	return page;
}

// Allocate a page in memory
void *alloc_page(page_table_entry *page) {
	void *frame = pmm_alloc_frames(1);
	if (frame) {
		SET_FRAME(page, (phys_addr_t)frame);
		SET_ATTRIBUTE(page, PTE_PRESENT);
	}
	return frame;
}

// Free a page in memory
void free_page(page_table_entry *page) {
	void *address = (void *)PAGE_GET_PHYSICAL_ADDRESS(page);
	if (address)
		pmm_free_frames(address, 1);
	CLEAR_ATTRIBUTE(page, PTE_PRESENT);
}

// Set the current page directory
bool switch_page_directory(page_directory_t *dir) {
	if (!dir) return false;

	current_directory = dir;
	ASM("movl %%eax, %%cr3":: "a"(current_directory));

	return true;
}

// Flush a single page in TLB
void flush_tlb_entry(virt_addr_t address) {
	ASM("cli; invlpg (%0); sti":: "r"(address) );
}

// Map a page
bool map_page(void *p_addr, void *v_addr) {
	// Get page
	page_directory_t *dir = current_directory;

	// Get page table
	page_directory_entry *entry = &dir->entries[PAGE_DIRECTORY_INDEX((uint32_t)v_addr)];

	if ((*entry & PTE_PRESENT) != PTE_PRESENT) {
		page_table_t *table = (page_table_t *)pmm_alloc_frames(1);
		if (!table) return false;

		memset(table, 0, sizeof(page_table_t));

		page_directory_entry *entry = &dir->entries[PAGE_DIRECTORY_INDEX((uint32_t)v_addr)];
		SET_ATTRIBUTE(entry, PDE_PRESENT | PDE_READ_WRITE);
		SET_FRAME(entry, (phys_addr_t)table);
	}

	page_table_t *table = (page_table_t *)PAGE_GET_PHYSICAL_ADDRESS(entry);
	page_table_entry *page = &table->entries[PAGE_TABLE_INDEX((uint32_t)v_addr)];

	SET_ATTRIBUTE(page, PTE_PRESENT);
	SET_FRAME(page, (phys_addr_t)p_addr);

	return true;
}

// Unmap a page
void unmap_page(void *v_addr) {
	page_table_entry *page = get_page((uint32_t)v_addr);

	SET_FRAME(page, 0); // Set physical address to 0
	CLEAR_ATTRIBUTE(page, PTE_PRESENT); // Clear present flag
}

// Initialise the virtual memory manager
bool vmm_init(void) {
	page_directory_t *dir = (page_directory_t *)pmm_alloc_frames(3);
	if (!dir) return false;

	// Clear the page directory
	memset(dir, 0, sizeof(page_directory_t));
	for (int i = 0; i < TABLES_PER_DIR; i++) {
		dir->entries[i] = 0x02; // supervisor, read/write, not present
	}

	page_table_t *table = (page_table_t *)pmm_alloc_frames(1);

	if (!table) return false; // Out of memory

	// Allocate a 3GB page table
	page_table_t *table3G = (page_table_t *)pmm_alloc_frames(1);

	if (!table3G) return false; // Out of memory

	// Clear the page table
	memset(table, 0, sizeof(page_table_t));
	memset(table3G, 0, sizeof(page_table_t));

	// Identity map the first 4MB
	for (uint32_t i = 0, frame = 0x0, virt = 0x0; i < PAGE_PER_TABLE; i++, frame += PAGE_SIZE, virt += PAGE_SIZE) {
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

	page_directory_entry *entry = &dir->entries[PAGE_DIRECTORY_INDEX(0xC0000000)];
	SET_ATTRIBUTE(entry, PDE_PRESENT | PDE_READ_WRITE);
	SET_FRAME(entry, (phys_addr_t)table);

	page_directory_entry *entry2 = &dir->entries[PAGE_DIRECTORY_INDEX(0x00000000)];
	SET_ATTRIBUTE(entry2, PDE_PRESENT | PDE_READ_WRITE);
	SET_FRAME(entry2, (phys_addr_t)table3G);

	// panic("Virtual memory manager initialised\n");
	// Switch to the new page directory
	switch_page_directory(dir);

	// Enable paging: Set PG bit 31 and PE bit 0 of CR0
	ASM("movl %cr0, %eax; orl $0x80000001, %eax; movl %eax, %cr0");

	return true;	
}