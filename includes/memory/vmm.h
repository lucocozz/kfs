#ifndef KERNEL_MEMORY_VMM_H
#define KERNEL_MEMORY_VMM_H

#include "system/utils.h"

#define PAGE_PER_TABLE	1024
#define TABLES_PER_DIR	1024
#define PAGE_SIZE		4096

#define PAGE_DIRECTORY_INDEX(v_addr)			((v_addr) >> 22)
#define PAGE_TABLE_INDEX(v_addr)				(((v_addr) >> 12) & 0x3FF)
#define PAGE_GET_PHYSICAL_ADDRESS(dir_entry)	(*dir_entry & ~0xFFF)
#define SET_ATTRIBUTE(entry, attribute)			(*entry |= attribute)
#define CLEAR_ATTRIBUTE(entry, attribute)		(*entry &= ~attribute)
#define TEST_ATTRIBUTE(entry, attribute)		(*entry & attribute)
#define SET_FRAME(entry, addr)					(*entry = (*entry & ~0x7FFFF000) | addr) // only set the frame address not the flags

#define ERR_OUT_OF_MEMORY	-1


typedef uint32_t page_table_entry;
typedef uint32_t page_directory_entry;


typedef enum PTE_flags {
	PTE_PRESENT 		= 0x01,
	PTE_READ_WRITE 		= 0x02,
	PTE_USER 			= 0x04,
	PTE_WRITETHROUGH 	= 0x08,
	PTE_NOT_CACHEABLE 	= 0x10,
	PTE_ACCESSED 		= 0x20,
	PTE_DIRTY 			= 0x40,
	PTE_PAT 			= 0x80,
	PTE_CPU_GLOBAL 		= 0x100,
	PTE_FRAME 			= 0x7FFFF000,
} PTE_flags_t;

typedef enum PDE_flags {
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
} PDE_flags_t;

// page table: handles 4MB of memory

typedef struct page_table {
	page_table_entry entries[PAGE_PER_TABLE];
} page_table_t;

// page directory: handles 4GB of memory
typedef struct page_directory {
	page_directory_entry entries[TABLES_PER_DIR];
} page_directory_t;


typedef struct page_free {
	size_t				count;
	struct page_free	*next;
} page_free_t;


extern page_directory_t	*g_current_directory;
extern uint32_t			g_placement_address;

extern page_free_t		*g_free_list;


int						vmm_init(void);
void					*vmm_alloc_page(page_table_entry *page);
void					vmm_free_page(page_table_entry *page);
bool					vmm_map_page(uint32_t *p_addr, uint32_t *v_addr);
void					vmm_unmap_page(uint32_t *v_addr);
page_table_entry		*vmm_get_page(const uint32_t v_addr);
page_table_entry		*vmm_get_page_table_entry(page_table_t *table, uint32_t v_addr);
page_directory_entry	*vmm_get_page_directory_entry(page_directory_t *dir, uint32_t v_addr);

int		munmap(void *addr, size_t size);
void	*mmap(size_t size);
void	print_free_list(void);

#endif