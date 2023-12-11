unistd = files([

])

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

io = files([
	'sys/io/write_port.c',
	'sys/io/read_port.c',
])

sys = files([

])
sys += io

libc_includes = include_directories('./includes')

libc_sources = (
	unistd +
	stdio +
	stdlib +
	string +
	sys
)