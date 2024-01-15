.global load_idt

# load_idt - Loads the interrupt descriptor table (IDT).
# stack: [esp + 4] the address of the first entry in the IDT
#        [esp    ] the return address

load_idt:
    movl 4(%esp), %eax    # Load the address of the first entry in the IDT
    lidt (%eax)           # Load the IDT
    ret                   # Return
