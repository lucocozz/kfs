
subdir('libk')
subdir('libc')

libk = static_library(
	'libk',
	libk_sources,
	link_args: cflags,
	include_directories: [libk_includes, libc_includes],
)

libc = static_library(
	'libc',
	libc_sources,
	link_args: cflags,
	include_directories: [libc_includes, libk_includes],
	link_with: libk,
)

libs_includes = [
	libc_includes,
	libk_includes,
]

libs = [
	libc,
	libk,
]