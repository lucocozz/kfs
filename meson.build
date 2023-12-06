project(
	'kfs-1', 'c',
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
]

cc = meson.get_compiler('c')

foreach cflag : cflags
	if cc.has_argument(cflag)
		add_project_arguments(cflag, language: 'c')
	endif
endforeach

subdir('sources')

executable(
	meson.project_name(),
	sources,
	include_directories: include_directories('includes'),
	link_args: cflags,
)
