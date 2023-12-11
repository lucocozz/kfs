
subdir('libc')
subdir('libk')

libc = static_library(
	'libc',
	libc_sources,
	link_args: cflags,
	include_directories: libc_includes,
)

libk = static_library(
	'libk',
	libk_sources,
	link_args: cflags,
	include_directories: libk_includes,
)


libs_includes = [
	libc_includes,
	libk_includes,
]

libs = [
	libc,
	libk,
]