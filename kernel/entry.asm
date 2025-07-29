; Kernel entry point
; This file contains the assembly code that interfaces with the bootloader

BITS 32

section .text
global _start
extern kernel_main

_start:
    ; Set up stack
    mov esp, stack_top
    
    ; Clear interrupts
    cli
    
    ; Call the main kernel function
    call kernel_main
    
    ; If kernel_main returns, halt the system
    cli
    hlt
.hang:
    jmp .hang

section .bss
    resb 8192       ; 8KB stack
stack_top:
