kernel_includes = include_directories('../includes')

subdir('driver')
subdir('interrupt')
subdir('boot')
subdir('printk')
subdir('shell')
subdir('memory')

kernel_c_sources = files(['kernel.c', 'symbol_table.c'])
kernel_asm_sources = files([])

kernel_c_sources += (
	driver +
	interrupt_c +
	printk +
	shell +
	memory_c
)

kernel_asm_sources += (
	boot_asm +
	interrupt_asm +
	memory_asm
)

