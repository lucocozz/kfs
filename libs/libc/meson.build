
stdio = files([

])

stdlib = files([

])


string = files([
	'string/strlen.c',
	'string/strcat.c',
	'string/strncat.c',
	'string/strchr.c',
	'string/strrchr.c',
	'string/strcmp.c',
	'string/strncmp.c',
	'string/strcpy.c',
	'string/strncpy.c',
])


libc_includes = include_directories('./includes')

libc_sources = (
	stdio +
	stdlib +
	string
)