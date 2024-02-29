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
BootPageDirectory:
    ; This page directory entry identity-maps the first 4MB of the 32-bit physical address space.
    ; All bits are clear except the following:
    ; bit 7: PS The kernel page is 4MB.
    ; bit 1: RW The kernel page is read/write.
    ; bit 0: P  The kernel page is present.
    ; This entry must be here -- otherwise the kernel will crash immediately after paging is
    ; enabled because it can't fetch the next instruction! It's ok to unmap this page later.
    dd 0x00000083                                       ; 0b10000011 (PSE=1, RW=1, P=1)
    times (KERNEL_PAGE_NUMBER - 1) dd 0                 ; Pages before kernel space.
    ; This page directory entry defines a 4MB page containing the kernel. Since 0xC0000000 translates to the index 768, we set the 768th entry in the page directory to point to the 4MB page containing the kernel.
    dd 0x00000083
    times (1024 - KERNEL_PAGE_NUMBER - 1) dd 0  ; Pages after the kernel image.
 
 
section .text
align 4
MultiBootHeader:
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
 
; setting up entry point for linker
global _start
_start:
    ; NOTE: Until paging is set up, the code must be position-independent and use physical
    ; addresses, not virtual ones!
    mov ecx, (BootPageDirectory - KERNEL_VIRTUAL_ADDRESS)
    mov cr3, ecx                                        ; Load Page Directory Base Register.
 
    mov ecx, cr4
    or ecx, PSE_FLAG                          ; Set PSE bit in CR4 to enable 4MB pages.
    mov cr4, ecx
 
    mov ecx, cr0
    or ecx, PG_FLAG                          ; Set PG bit in CR0 to enable paging.
    mov cr0, ecx
 
    ; Start fetching instructions in kernel space.
    ; Since eip at this point holds the physical address of this command (approximately 0x00100000)
    ; we need to do a long jump to the correct virtual address of StartInHigherHalf which is
    ; approximately 0xC0100000.
    lea ecx, [HigherHalfKernel]
    jmp ecx                                                     ; NOTE: Must be absolute jump!
 
HigherHalfKernel:
    ; Unmap the identity-mapped first 4MB of physical address space. It should not be needed
    ; anymore.
    mov dword [BootPageDirectory], 0
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