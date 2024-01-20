.global load_page_directory

load_page_directory:
    movl 4(%esp), %eax    
    movl %cr3, %ebx
    andl $0xfff, %ebx     
    andl $0xfffff000, %eax
    orl %eax, %ebx        
    movl %ebx, %cr3       
    ret

.global enable_paging

enable_paging:
    # enable 4MB paging
    movl %cr4, %eax    # read current cr4
    orl $0x10, %eax     # set PSE
    movl %eax, %cr4     # update cr4

    # enable paging (PG bit)
    movl %cr0, %eax     # read current cr0
    orl $0x80000001, %eax  # set PE (bit 0) and PG (bit 31)
    movl %eax, %cr0     # update cr0
    ret