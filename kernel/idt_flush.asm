global idt_flush

idt_flush:
    mov eax, [esp+4]    ; Get the pointer to the IDT descriptor
    lidt [eax]          ; Load the IDT
    ret
