#ifndef VMM_H
# define VMM_H

#include "system/utils.h"

# define PAGE_PER_TABLE 1024
# define TABLES_PER_DIR 1024
# define PAGE_SIZE 4096

#define PAGE_DIRECTORY_INDEX(virt_addr) ((virt_addr) >> 22)
#define PAGE_TABLE_INDEX(virt_addr) (((virt_addr) >> 12) & 0x3FF)
#define PAGE_GET_PHYSICAL_ADDRESS(dir_entry) (*dir_entry & ~0xFFF)
#define SET_ATTRIBUTE(entry, attribute) (*entry |= attribute)
#define CLEAR_ATTRIBUTE(entry, attribute) (*entry &= ~attribute)
#define TEST_ATTRIBUTE(entry, attribute) (*entry & attribute)
#define SET_FRAME(entry, addr) (*entry = (*entry & ~0x7FFFF000) | addr) // only set the frame address not the flags

typedef uint32_t page_table_entry;
typedef uint32_t page_directory_entry;
typedef uint32_t phys_addr;
typedef uint32_t virt_addr;

typedef enum {
	PTE_PRESENT 		= 0x01,
	PTE_READ_WRITE 		= 0x02,
	PTE_USER 			= 0x04,
	PTE_WRITETHROUGH 	= 0x08,
	PTE_NOT_CACHEABLE 	= 0x10,
	PTE_ACCESSED 		= 0x20,
	PTE_DIRTY 			= 0x40, // 
	PTE_PAT 			= 0x80,
	PTE_CPU_GLOBAL 		= 0x100,
	PTE_FRAME 			= 0x7FFFF000,
} page_table_entry_flags;

typedef enum {
	PDE_PRESENT 		= 0x01,
	PDE_READ_WRITE 		= 0x02,
	PDE_USER 			= 0x04,
	PDE_WRITETHROUGH 	= 0x08,
	PDE_NOT_CACHEABLE 	= 0x10,
	PDE_ACCESSED 		= 0x20,
	PDE_DIRTY 			= 0x40,
	PDE_4MB 			= 0x80, // 0 = 4KB, 1 = 4MB
	PDE_CPU_GLOBAL 		= 0x100,
	PDE_PAT 			= 0x2000,
	PDE_FRAME 			= 0x7FFFF000,
} page_directory_entry_flags;

// page table: handles 4MB of memory

typedef struct {
	page_table_entry entries[PAGE_PER_TABLE];
} page_table_t;

// page directory: handles 4GB of memory
typedef struct {
	page_directory_entry entries[TABLES_PER_DIR];
} page_directory_t;

extern page_directory_t *current_directory;

// Get entry from page table for a given virtual address
page_table_entry *get_page_table_entry(page_table_t *table, virt_addr address);

// Get entry from page directory for a given virtual address
page_directory_entry *get_page_directory_entry(page_directory_t *dir, virt_addr address);

// Return a page table entry for a given virtual address
page_table_entry *get_page(const virt_addr address);

// Allocate a page in memory
void *alloc_page(page_table_entry *page);

// Free a page in memory
void free_page(page_table_entry *page);

// Set the current page directory
bool switch_page_directory(page_directory_t *dir);

// Flush a single page in TLB
void flush_tlb_entry(virt_addr address);

// Map a page
bool map_page(void *paddr, void *vaddr);

// Unmap a page
void unmap_page(void *virt_addr);

// Initialise the virtual memory manager
bool initialise_virtual_memory_manager(void);

#endif