#ifndef KERNEL_MEMORY_PAGING_H
#define KERNEL_MEMORY_PAGING_H

#include <stdint.h>
#include <stddef.h>

#define __packed __attribute__((packed))
#define __aligned(x) __attribute__((aligned(x)))

#define PAGE_SIZE 4096
#define PAGE_TABLE_SIZE 1024
#define PAGE_DIRECTORY_SIZE 1024

typedef struct page_directory {
	uint32_t present		: 1;
	uint32_t read_write		: 1;
	uint32_t user_supervisor: 1;
	uint32_t write_through	: 1;
	uint32_t cache_disabled	: 1;
	uint32_t accessed		: 1;
	uint32_t dirty			: 1;
	uint32_t page_size		: 1;
	uint32_t global			: 1;
	uint32_t available		: 3;
	uint32_t page_table		: 20;
} __packed page_directory_t;

typedef struct page_table {
	uint32_t present		: 1;
	uint32_t read_write		: 1;
	uint32_t user_supervisor: 1;
	uint32_t write_through	: 1;
	uint32_t cache_disabled	: 1;
	uint32_t accessed		: 1;
	uint32_t dirty			: 1;
	uint32_t page_table		: 1;
	uint32_t global			: 1;
	uint32_t available		: 3;
	uint32_t page_frame		: 20;
} __packed page_table_t;

extern page_directory_t page_directory[PAGE_DIRECTORY_SIZE] __aligned(PAGE_SIZE);

#endif
