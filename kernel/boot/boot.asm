global _start_                          ; Make entry point visible to linker.
extern kernel_main                      ; main is defined elsewhere
 
; MULTI_BOOT_HEADER
%define ALIGN  (1<<0)                   ; align loaded modules on page boundaries
%define MEMINFO      (1<<1)             ; provide memory map
%define FLAGS        (ALIGN | MEMINFO)  ; this is the Multiboot 'flag' field
%define MAGIC        0x1BADB002         ; 'magic number' lets bootloader find the header
%define CHECKSUM     -(MAGIC + FLAGS)   ; checksum required
 
; reserve initial kernel stack space, that's 16k.
%define STACKSIZE 0x4000 * 8
 
section .text
align 4
MultiBootHeader:
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
 
 	dd 0
	dd 0
	dd 0
	dd 0
	dd 0

	dd 1
	dd 800
	dd 400
	dd 32

; setting up entry point for linker
global _start
_start:
	mov esp, stack_top                  ; Set up initial stack pointer.
	push esp                            ; pass stack pointer
	push ebx                            ; pass Multiboot info structure
	push eax                            ; pass Multiboot magic number 

	cli 
	extern kernel_main
	call kernel_main

halt:	hlt
	jmp halt

 
section .bss
align 32
stack_bottom:
	resb STACKSIZE      ; reserve 16k stack on a uint64_t boundary
stack_top:
