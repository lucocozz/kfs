ENTRY(_start)
OUTPUT_FORMAT(elf32-i386)
KERNEL_VIRTUAL_ADDRESS = 0xC0100000;

SECTIONS {
	/* The kernel will live at 3GB + 1MB in the virtual
		address space, which will be mapped to 1MB in the
		physical address space. */
	. = KERNEL_VIRTUAL_ADDRESS;

	_kernel_start = .;

	.text ALIGN (0x1000) : AT(ADDR(.text) - 0xC0000000) {
		_stext = .;    
		*(.text)
		_etext = .;
	}

	.rodata ALIGN (0x1000) : AT(ADDR(.rodata) - 0xC0000000) {
		_srodata = .;
		*(.rodata*)
		_erodata = .;
	}

	.data ALIGN (0x1000) : AT(ADDR(.data) - 0xC0000000) {
		_sdata = .;
		*(.data)
		_edata = .;
	}

	.bss ALIGN (0x1000) : AT(ADDR(.bss) - 0xC0000000) {
		_sbss = .;
		*(COMMON)
		*(.bss)
		_ebss = .;
	}

	_kernel_end = .;
}