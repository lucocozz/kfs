global enable_paging

enable_paging:
    mov eax, [esp+4]    ; 1st parameter : pointer to the page directory
    mov cr3, eax
    mov eax, cr0
    or eax, 0x80000000  ; set the PG bit
    mov cr0, eax
    ret