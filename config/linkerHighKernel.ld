ENTRY(_start)
OUTPUT_FORMAT(elf32-i386)
KERNEL_VIRTUAL_ADDRESS = 0xC0100000;

SECTIONS {
	/* The kernel will live at 3GB + 1MB in the virtual
		address space, which will be mapped to 1MB in the
		physical address space. */
	. = KERNEL_VIRTUAL_ADDRESS;

	_kernel_start_physical = 0x100000;
	_kernel_start_virtual = .;

	.text BLOCK(4K) : AT(ADDR(.text) - 0xC0000000) ALIGN (4K) {
		_stext = .;    
		*(.text)
		_etext = .;
	}

	.rodata BLOCK(4K) : AT(ADDR(.rodata) - 0xC0000000) ALIGN (4K) {
		_srodata = .;
		*(.rodata*)
		_erodata = .;
	}

	.data BLOCK(4K) : AT(ADDR(.data) - 0xC0000000) ALIGN (4K) {
		_sdata = .;
		*(.data)
		_edata = .;
	}

	.bss BLOCK(4K) : AT(ADDR(.bss) - 0xC0000000) ALIGN (4K) {
		_sbss = .;
		*(COMMON)
		*(.bss)
		_ebss = .;
	}

	_kernel_end_virtual = .;
	_kernel_end_physical = . - 0xC0000000;
}