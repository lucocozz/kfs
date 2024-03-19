ENTRY(_start)
OUTPUT_FORMAT(elf32-i386)
KERNEL_VIRTUAL_ADDRESS = 0x100000;

SECTIONS {
	. = 0x00100000;

	_kernel_start_physical = .;
	_kernel_start_virtual  = .;

	.text BLOCK(4K) : ALIGN (4K) {
		_stext = .;    
		*(.text)
		_etext = .;
	}

	.rodata BLOCK(4K) : ALIGN (4K) {
		_srodata = .;
		*(.rodata*)
		_erodata = .;
	}

	.data BLOCK(4K) : ALIGN (4K) {
		_sdata = .;
		*(.data)
		_edata = .;
	}

	.bss BLOCK(4K) : ALIGN (4K) {
		_sbss = .;
		*(COMMON)
		*(.bss)
		_ebss = .;
	}

	_kernel_end_virtual = .;
	_kernel_end_physical = .;
}