project(
	'kfs', ['c'],
	version: '0.2.0',
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
	# '-Wl,--print-map',
	# '-Wl,--undefined=symbol_table'
]

linker = ['-T', '../config/linker.ld']
link_args = cflags + linker + ['-static', '-Wl,--build-id=none']

cc = meson.get_compiler('c')

foreach cflag : cflags
	if cc.has_argument(cflag)
		add_project_arguments(cflag, language: 'c')
	endif
endforeach

subdir('libs')
subdir('kernel')


executable(
	meson.project_name() + '.bin',
	kernel_sources,
	include_directories: libs_includes + kernel_includes,
	link_args: link_args,
	link_with: libs,
)
