extern isr_callbacks

%macro no_error_code_irq 1
global irq_%1
irq_%1:
	push dword 0	; push 0 as error code
	push dword %1	; push the interrupt number
	jmp	call_isr	; jump to the common handler
%endmacro

%macro error_code_irq 1
global irq_%1
irq_%1:
	push dword 1	; push 1 as error code
	push dword %1	; push the interrupt number
	jmp call_isr	; jump to the common handler
%endmacro


call_isr:
	; save the registers
	push eax
	push ebx
	push ecx
	push edx
	push ebp
	push esi
	push edi

    call isr_callbacks

    ; restore the registers
	pop	edi
	pop	esi
	pop	ebp
	pop	edx
	pop	ecx
	pop	ebx
	pop eax

	; restore the esp
	add esp, 8

	; return to the code that got interrupted
	iret

no_error_code_irq 0	; create handler for interrupt 0 (divide by zero)
no_error_code_irq 14	; create handler for interrupt 14 (page fault)
no_error_code_irq 33	; create handler for interrupt 33 (keyboard)
error_code_irq 128	; create handler for interrupt 128 (syscall)