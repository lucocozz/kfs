# Define external interrupt_handler symbol
.global interrupt_handler

# Macro for no-error-code interrupt handler
.macro no_error_code_interrupt_handler int_number
    .global interrupt_handler_\int_number
interrupt_handler_\int_number:
    pushl   $0                           # push 0 as error code
    pushl   $\int_number                  # push the interrupt number
    jmp     common_interrupt_handler    # jump to the common handler
.endm

# Macro for error-code interrupt handler
.macro error_code_interrupt_handler int_number
    .global interrupt_handler_\int_number
interrupt_handler_\int_number:
    pushl   $\int_number                  # push the interrupt number
    jmp     common_interrupt_handler    # jump to the common handler
.endm

common_interrupt_handler:
    # save the registers
    pushl   %eax
    pushl   %ebx
    pushl   %ecx
    pushl   %edx
    pushl   %ebp
    pushl   %esi
    pushl   %edi

    # call the C function
    call    interrupt_handler

    # restore the registers
    popl    %edi
    popl    %esi
    popl    %ebp
    popl    %edx
    popl    %ecx
    popl    %ebx
    popl    %eax

    # restore the esp
    addl    $8, %esp

    # return to the code that got interrupted
    iret

# Example usage: create a handler for interrupt 33 (keyboard)
no_error_code_interrupt_handler   33
