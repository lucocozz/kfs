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
	'string/memcpy.c',
	'string/memset.c',
	'string/memcmp.c',
])

ctype = files([
	'ctype/isalnum.c',
	'ctype/isalpha.c',
	'ctype/iscntrl.c',
	'ctype/isdigit.c',
	'ctype/isgraph.c',
	'ctype/islower.c',
	'ctype/isprint.c',
	'ctype/ispunct.c',
	'ctype/isspace.c',
	'ctype/isupper.c',
	'ctype/isxdigit.c',
	'ctype/isascii.c',
	'ctype/isblank.c',
	'ctype/tolower.c',
	'ctype/toupper.c',
])

io = files([
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
	sys +
	ctype
)