# KFS

    - LDFLAGS=-N -Ttext=0x10000 , set up FLAGS au linker
    - Add user mode, https://singpolyma.net/2012/01/writing-a-simple-os-kernel-user-mode/

## Interupt table:
https://www.ctyme.com/intr/int.htm

## Paging :

Registers:
- https://wiki.osdev.org/CPU_Registers_x86

Segmentation VS Paging :
- https://www.geeksforgeeks.org/difference-between-paging-and-segmentation/
- https://www.youtube.com/watch?v=pcvKrvEJRgg
- https://www.youtube.com/watch?v=p9yZNLeOj4s

General:
- https://wiki.osdev.org/Memory_Management_Unit
- https://en.wikipedia.org/wiki/Memory_management_unit#:~:text=A%20memory%20management%20unit%20(MMU,physical%20addresses%20in%20main%20memory.
- https://wiki.osdev.org/CPU_Registers_x86#Control_Registers
- https://wiki.osdev.org/Paging




Paging divides memory by pages.
CPU seems to have some registers to be dedicated to that purpose (CR0 bit 31, CR2, CR3, CR4 bit 4...)
The Protected mode registers are also really interesting, (GDT, IDT, LDT)
Also it seems that to activate or deactivate protected mode: CR0 bit 0, CR4 bit 1

Our kernel is put into memory by grub in a specific address, activating paging allows us to act like our kernel is located in the Higher Half Kernel (Virtual address: 0xC0000000 -> 0xFFFFFFFF)
This paragraph is interesting: https://wiki.osdev.org/Memory_Management_Unit#Discourse_on_Memory_Management_Units_and_Virtual_Memory_systems_in_contemporary_architectures

When not activated all address bypass the MMU and they (the address) are thus not translated from virtual to physical address. They get put onto the "address bus" as they are.

The TLB (Translation Lookaside Buffer) is a cache of memory, ease the tranlation from virtual to physical adresses. It needs to be flushed or some addresses, otherwise he could try to access released/unused memory.
OK so we can do this two way, either we just ensure to flush datas when released or we get full control of the TLB content and so have to ensure coherency ourself.




Side-Notes:
- We should research about debug extensions (CR4 bit 3, DR*)
- In segments.c add - 1 to the gdt_ptr limit
- Flags bits are not set in gdt_set_gate [ref](https://www.youtube.com/watch?v=jwulDRMQ53I&list=PL2EF13wm-hWAglI8rRbdsCPq_wRpYvQQy&index=3)
-
- https://github.com/lucocozz/kfs/blob/paging/includes/multiboot.h Uint64 needs to be 32
