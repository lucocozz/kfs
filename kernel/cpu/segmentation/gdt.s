.global gdt_flush	# extern void gdt_flush();

gdt_flush:
    movl 4(%esp), %eax  # load the address of the gdt
    lgdt (%eax)          # load the gdt

    movw $0x10, %ax      # load the data segment selector
    movw %ax, %ds        # set the data segment
    movw %ax, %es        # set the extra segment
    movw %ax, %fs        # set the fs segment
    movw %ax, %gs        # set the gs segment
    movw %ax, %ss        # set the stack segment
    ljmp $0x08, $.flush  # jump to the code segment

.flush:
    ret                  # return
