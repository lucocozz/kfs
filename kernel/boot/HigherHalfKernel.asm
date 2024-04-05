global _start_                          ; Make entry point visible to linker.
extern kernel_main                      ; main is defined elsewhere

; MULTI_BOOT_HEADER
%define ALIGN  (1<<0)                   ; align loaded modules on page boundaries
%define MEMINFO      (1<<1)             ; provide memory map
%define FLAGS        (ALIGN | MEMINFO)  ; this is the Multiboot 'flag' field
%define MAGIC        0x1BADB002         ; 'magic number' lets bootloader find the header
%define CHECKSUM     -(MAGIC + FLAGS)   ; checksum required
 
; CONSTANTS FOR PAGING
%define KERNEL_VIRTUAL_ADDRESS 0xC0000000                  ; 3GB
%define KERNEL_PHYSICAL_ADDRESS 0x00100000                 ; 1MB
%define KERNEL_PAGE_NUMBER (KERNEL_VIRTUAL_ADDRESS >> 22)  ; Page directory index of kernel's 4MB PTE.
 
%define PSE_FLAG 0x00000010
%define PG_FLAG 0x80000000

; reserve initial kernel stack space, that's 16k.
%define STACKSIZE 0x4000 * 8
 
section .data
align 0x1000
boot_page_directory:
	resb 4096
boot_page_table1:
	resb 4096

extern _kernel_start_physical
extern _kernel_end_physical

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
	mov edi, dword (boot_page_table1 - 0xC0000000)
	mov esi, dword 0
	mov ecx, dword 1023

uno:
	cmp esi, dword _kernel_start_physical
	jl dos
	cmp esi, dword (_kernel_end_physical - 0xC0000000)
	jge tres

	mov edx, esi
	or edx, dword 0x003
	mov [edi], edx

dos:
	add esi, dword 4096
	add edi, dword 4
	loop uno

tres:
	mov dword [boot_page_table1 - 0xC0000000 + 1023 * 4], (0x000B8000 | 0x003)

	mov dword [boot_page_directory - 0xC0000000 + 0], (boot_page_table1 - 0xC0000000 + 0x003)
	mov dword [boot_page_directory - 0xC0000000 + 768 * 4], (boot_page_table1 - 0xC0000000 + 0x003)

	mov ecx, dword (boot_page_directory - 0xC0000000)
	mov cr3, ecx

	mov ecx, cr0
	or ecx, dword 0x80010000
	mov cr0, ecx

	lea ecx, [HigherHalfKernel]
	jmp ecx

HigherHalfKernel:
	; Unmap the identity-mapped first 4MB of physical address space. It should not be needed
	; anymore.
	; mov dword [BootPageDirectory], 0
	invlpg [0]                          ; Invalidate TLB for the first page.
 
	; NOTE: From now on, paging should be enabled. The first 4MB of physical address space is
	; mapped starting at KERNEL_VIRTUAL_ADDRESS. Everything is linked to this address, so no more
	; position-independent code or funny business with virtual-to-physical address translation
	; should be necessary. We now have a higher-half kernel.

	mov esp, stack_top                  ; Set up initial stack pointer.

	push esp                            ; pass stack pointer
	push ebx                            ; pass Multiboot info structure
	push eax                            ; pass Multiboot magic number 

	cli 
	extern kernel_main
	call kernel_main 
	
	cli
halt:
	hlt
	jmp halt
 
section .bss
align 32
stack_bottom:
	resb STACKSIZE      ; reserve 16k stack on a uint64_t boundary
stack_top: