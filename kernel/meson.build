kernel_includes = include_directories('../includes')

subdir('driver')
subdir('cpu')
subdir('boot')
subdir('printk')
subdir('builtin')

kernel_sources = files(['kernel.c', 'symbol_table.c'])

kernel_sources += (
	driver +
	cpu +
	boot +
	printk +
	builtin
)
