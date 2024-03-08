;Generic Interrupt Handler
;
extern isr_callbacks

%macro no_error_code_isr 1
global isr_%1
isr_%1:
	push dword 0	; push 0 as error code
	push dword %1	; push the interrupt number
	jmp	call_isr	; jump to the common handler
%endmacro

%macro error_code_isr 1
global isr_%1
isr_%1:
	push dword 1	; push 1 as error code
	push dword %1	; push the interrupt number
	jmp call_isr	; jump to the common handler
%endmacro


call_isr:               ; the common parts of the generic interrupt handler
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
	pop     eax

	; restore the esp
	add     esp, 8

	; return to the code that got interrupted
	iret

no_error_code_isr 14	; create handler for interrupt 14 (page fault)
no_error_code_isr 33	; create handler for interrupt 33 (keyboard)