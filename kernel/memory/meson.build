subdir('virtual')
subdir('physical')
subdir('paging')
subdir('segmentation')
subdir('memory_map')
subdir('utils')


memory_c = files([
	'memory_init.c',
])

memory_c += [
	virtual,
	physical,
	segmentation_c,
	paging,
	memory_map,
	utils
]

memory_asm = segmentation_asm
