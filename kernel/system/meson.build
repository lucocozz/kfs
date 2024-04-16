subdir('interrupts')
subdir('utils')
subdir('signals')

system_c = files([])
system_asm = files([])

system_c += (
	interrupts_c +
	utils +
	signals
)
system_asm += interrupts_asm
