global  idt_load

; idt_load - Loads the interrupt descriptor table (IDT).
; stack: [esp + 4] the address of the first entry in the IDT
;        [esp    ] the return address

idt_load:
    mov eax, [esp + 4]
    lidt [eax]
    ret

