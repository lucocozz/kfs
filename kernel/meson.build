kernel_includes = include_directories('../includes')

subdir('driver')
subdir('cpu')
subdir('boot')
subdir('printk')
subdir('shell')
subdir('memory')

kernel_c_sources = files(['kernel.c', 'symbol_table.c'])
kernel_asm_sources = files([])

kernel_c_sources += (
	driver +
	cpu_c +
	printk +
	shell +
	memory
)

kernel_asm_sources += (
	boot_asm +
	cpu_asm
)

