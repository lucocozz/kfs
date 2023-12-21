kernel_includes = include_directories('../includes')

kernel_sources = files([
	'kernel.c',

	'boot/boot.s',
	'boot/crti.s',
	'boot/crtn.s',

	'cpu/idt.s',
	'cpu/interrupt_handlers.s',
	'cpu/interrupts.c',
	'cpu/pic.c',

	'driver/tty.c',
	'driver/keyboard.c',
	'driver/vga.c',
	'driver/ports.c',
])
