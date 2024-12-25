.intel_syntax noprefix
.global _start
.data
buffer:
    .fill 4096, 1, 0
.text
_start:
    mov rbx, 0  
loop:
    mov rax, 0
    mov rdi, 0
    lea rsi, [buffer]
    mov rdx, 4096
    syscall

    mov rbx, rax
    cmp rbx, -1
    je exit_one

    cmp rbx, 0
    je exit_zero

    mov rax, 1
    mov rdi, 1
    lea rsi, [buffer]
    mov rdx, rbx
    syscall

    cmp rax, -1
    je exit_one

    jmp loop

exit_zero:
    mov rax, 60
    mov rdi, 0
    syscall
    jmp end
exit_one:
    mov rax, 60
    mov rdi, 1
    syscall
end:

