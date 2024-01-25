; Define constants for multiboot flags
MBOOT_PAGE_ALIGN EQU 1 << 0  ; Align loaded pages
MBOOT_MEM_INFO EQU 1 << 1    ; Provide memory information
MBOOT_USE_GFX EQU 0          ; No graphical interface

; Constants for the multiboot header
MBOOT_MAGIC EQU 0x1BADB002   ; Magic number for bootloader
MBOOT_FLAGS EQU MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO | MBOOT_USE_GFX ; Combination of flags
MBOOT_CHECKSUM EQU -(MBOOT_MAGIC + MBOOT_FLAGS) ; Checksum to verify header integrity

; Multiboot header section
section .multiboot
ALIGN 4
    DD MBOOT_MAGIC
    DD MBOOT_FLAGS
    DD MBOOT_CHECKSUM
    DD 0, 0, 0, 0, 0

    DD 0
    DD 800
    DD 600
    DD 32

; Stack section
SECTION .bss
ALIGN 16
stack_bottom:
    RESB 16384 * 8  ; Reserve space for stack
stack_top:

; Boot code section
section .boot

global _start
_start:
    ; Check if bootloader is multiboot compatible
    CMP eax, 0x2BADB002
    JNE not_multiboot

    MOV ecx, (initial_page_dir - 0xC0000000) ; Load address of page directory
    MOV cr3, ecx

    ; Enable 4MB paging
    MOV ecx, cr4
    OR ecx, 0x10
    MOV cr4, ecx

    ; Enable paging (PG bit in CR0)
    MOV ecx, cr0
    OR ecx, 0x80000000
    MOV cr0, ecx

    ; Check if paging is enabled
    MOV ecx, cr0
    TEST ecx, 0x80000000
    JZ paging_not_enabled

    ; Paging is now enabled
    JMP higher_half ; Jump to next code section




not_multiboot:
    ; Handle error: bootloader is not multiboot compatible
    LEA eax, [multiboot_error_message]
    PUSH eax
    CALL print_string
    ADD esp, 4
    JMP halt

paging_not_enabled:
    ; Handle error: paging was not enabled
    LEA eax, [paging_error_message]
    PUSH eax
    CALL print_string
    ADD esp, 4
    JMP halt

print_string:
    POP eax ; Get address of string from stack
    PUSH eax ; Push it back for later
    LODSB ; Load byte at address in SI into AL
    OR al, al ; Test if byte is zero
    JZ done_printing ; If byte is zero, end of string has been reached
    MOV ah, 0x0E ; Function number for teletype output
    INT 0x10 ; BIOS interrupt for video services
    JMP print_string ; Print next character

done_printing:
    POP eax ; Remove address of string from stack
    RET




; Main code section
section .text
higher_half:
    MOV esp, stack_top ; Initialize stack
    PUSH ebx
    PUSH eax
    XOR ebp, ebp
    extern kernel_main
    CALL kernel_main ; Call main kernel function

halt:
    hlt ; Halt processor
    JMP halt ; Infinite loop in case main function returns



; Data section
section .data
align 4096
multiboot_error_message db 'Error: Bootloader is not multiboot compatible', 0
paging_error_message db 'Error: Paging was not enabled', 0
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