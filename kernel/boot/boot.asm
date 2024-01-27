; Declare constants for the multiboot header.
%define ALIGN   (1 << 0)           ; align loaded modules on page boundaries
%define MEMINFO (1 << 1)           ; provide memory map
%define FLAGS   (ALIGN | MEMINFO)   ; this is the Multiboot 'flag' field
%define MAGIC   0x1BADB002         ; 'magic number' lets bootloader find the header
%define CHECKSUM -(MAGIC + FLAGS)  ; checksum of above, to prove we are multiboot

; Declare a header as in the Multiboot Standard.
section .multiboot
    align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

; Reserve a stack for the initial thread.
section .bss
    align 16
stack_bottom:
    resb 16384 * 8 ; 16 KiB
stack_top:

section .boot
 global _start
 _start:

    mov ecx, (initial_page_dir - 0xC0000000) ; Load address of page directory
    mov cr3, ecx

    ; Enable 4MB paging
    mov ecx, cr4
    or ecx, 0x10
    mov cr4, ecx

    ; Enable paging (PG bit in CR0)
    mov ecx, cr0
    or ecx, 0x80000000
    mov cr0, ecx

    jmp higher_half


section .text
higher_half:
    mov esp, stack_top
    push ebx
    push eax
    xor ebp, ebp
    extern kernel_main
    call kernel_main

halt:
    ; cli
    hlt
    jmp halt


section .data
align 4096
global initial_page_dir
initial_page_dir:
    ; The first entry of the page directory is used for self-referenced paging.
    ; 10000011b means the page is present, read/write, and user accessible.
    DD 10000011b

    ; Fill the next 767 entries with 0, which means these pages are not present.
    TIMES 768-1 DD 0

    ; The next 4 entries are used to map the first 4MB of physical memory
    ; to the virtual address 0xC0000000 (3GB). This is known as higher half mapping.
    ; (0 << 22) | 10000011b means the page at physical address 0x0 is present, read/write,
    ; user accessible, and mapped to the virtual address 0xC0000000.
    DD (0 << 22) | 10000011b

    ; Similarly, (1 << 22) | 10000011b means the page at physical address 0x400000 (4MB)
    ; is present, read/write, user accessible, and mapped to the virtual address 0xC0400000.
    DD (1 << 22) | 10000011b

    ; And so on for the next two entries.
    DD (2 << 22) | 10000011b
    DD (3 << 22) | 10000011b

    ; Fill the remaining 252 entries with 0, which means these pages are not present.
    TIMES 256-4 DD 0