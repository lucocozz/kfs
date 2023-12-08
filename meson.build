project(
	'kfs', ['c'],
	version: '0.1.0',
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
]

linker = ['-T', '../sources/arch/i386/linker.ld']
link_args = cflags + linker

cc = meson.get_compiler('c')
nasm = meson.get_compiler('nasm')

foreach cflag : cflags
	if cc.has_argument(cflag)
		add_project_arguments(cflag, language: 'c')
	endif
endforeach

subdir('libs')
subdir('sources')


executable(
	meson.project_name() + '.bin',
	sources,
	include_directories: libs_includes + [include_directories('includes')],
	link_args: link_args,
	link_with: libs,
)
