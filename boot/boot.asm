; Simple bootloader for CyberOS
; This bootloader loads the kernel from the second sector of the disk

BITS 16                     ; 16-bit real mode
ORG 0x7C00                  ; BIOS loads bootloader at 0x7C00

start:
    ; Initialize segment registers
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00          ; Set stack pointer

    ; Print boot message
    mov si, boot_msg
    call print_string

    ; Load kernel from disk
    mov ah, 0x02            ; BIOS read sectors function
    mov al, 5               ; Number of sectors to read
    mov ch, 0               ; Cylinder 0
    mov cl, 2               ; Start from sector 2 (after bootloader)
    mov dh, 0               ; Head 0
    mov dl, 0               ; Drive 0 (floppy)
    mov bx, 0x1000          ; Load kernel at 0x1000
    int 0x13                ; Call BIOS interrupt
    jc disk_error           ; Jump if error

    ; Switch to protected mode
    cli                     ; Disable interrupts
    lgdt [gdt_descriptor]   ; Load GDT
    
    mov eax, cr0
    or eax, 1               ; Set PE bit
    mov cr0, eax            ; Enable protected mode
    
    jmp 0x08:protected_mode ; Far jump to flush pipeline

disk_error:
    mov si, disk_error_msg
    call print_string
    hlt

print_string:
    mov ah, 0x0E            ; BIOS teletype function
.loop:
    lodsb                   ; Load byte from SI into AL
    test al, al             ; Check if null terminator
    jz .done
    int 0x10                ; Call BIOS interrupt
    jmp .loop
.done:
    ret

BITS 32
protected_mode:
    ; Set up protected mode segments
    mov ax, 0x10            ; Data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000        ; Set stack pointer

    ; Jump to kernel (loaded at 0x1000 but entry point is _start)
    jmp 0x1000
    
    ; If kernel returns, halt
    hlt

; Global Descriptor Table
gdt_start:
    ; Null descriptor
    dq 0
    
    ; Code segment descriptor
    dw 0xFFFF               ; Limit low
    dw 0                    ; Base low
    db 0                    ; Base middle
    db 10011010b            ; Access byte
    db 11001111b            ; Flags + Limit high
    db 0                    ; Base high
    
    ; Data segment descriptor
    dw 0xFFFF               ; Limit low
    dw 0                    ; Base low
    db 0                    ; Base middle
    db 10010010b            ; Access byte
    db 11001111b            ; Flags + Limit high
    db 0                    ; Base high
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; Size
    dd gdt_start                ; Offset

; Messages
boot_msg db 'CyberOS Bootloader v1.0', 0x0D, 0x0A, 'Loading kernel...', 0x0D, 0x0A, 0
disk_error_msg db 'Disk read error!', 0x0D, 0x0A, 0

; Boot signature
times 510-($-$$) db 0       ; Pad to 510 bytes
dw 0xAA55                   ; Boot signature
