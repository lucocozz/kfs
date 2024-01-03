kernel_includes = include_directories('../includes')

subdir('driver')
subdir('cpu')
subdir('boot')
subdir('printk')

kernel_sources = files(['kernel.c'])

kernel_sources += (
	driver +
	cpu +
	boot +
	printk
)
