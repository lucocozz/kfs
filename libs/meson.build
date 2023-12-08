
subdir('libc')

libc = static_library(
	'libc',
	libc_sources,
	link_args: cflags,
	include_directories: libc_includes,
)



libs_includes = [
	libc_includes,
]

libs = [
	libc,
]