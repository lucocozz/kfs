project(
	'kfs', ['c'],
	version: '0.3.0',
	default_options: [
		'warning_level=3',
		'werror=true',
	]
)

cflags = [
	'-m32',
	'-fno-builtin',
	'-fno-stack-protector',
	'-nostdlib',
	'-nodefaultlibs',
	'-ffreestanding',
	'-U__linux__',
	'-D__i386__',
	'-D__KERNEL__',
	'-D__HIGH_KERNEL__'
]

nasm_flags = [
	'-felf32',
	'-I./includes/',
]

# linker = ['-T', '../config/linker.ld']
linker = ['-T', '../config/linkerHighKernel.ld']
link_args = cflags + linker + ['-static', '-Wl,--build-id=none']

cc = meson.get_compiler('c')
nasm = find_program('nasm', required: true)


nasm_gen = generator(
	nasm,
	arguments: nasm_flags + ['@INPUT@', '-o', '@OUTPUT@'],
	output: '@PLAINNAME@.o',
)

foreach cflag : cflags
	if cc.has_argument(cflag)
		add_project_arguments(cflag, language: 'c')
	endif
endforeach

subdir('libs')
subdir('kernel')

kernel_asm_objects = nasm_gen.process(kernel_asm_sources)

executable(
	meson.project_name() + '.bin',
	kernel_c_sources,
	kernel_asm_objects,
	include_directories: libs_includes + kernel_includes,
	link_args: link_args,
	link_with: libs,
)
