global  idt_load

; idt_load - Loads the interrupt descriptor table (IDT).
idt_load:
    mov eax, [esp + 4] ; stack: [esp + 4] the address of the first entry in the IDT
    lidt [eax]
    ret

