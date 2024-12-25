.intel_syntax noprefix
.global sum
.text 

sum:
    mov r8d, ecx
    mov ecx, edi
instruct:
    mov r9d, [esi + 4 * ecx - 4]
    add r9d, [edx + 4 * ecx - 4]
    mov [r8d + 4 * ecx - 4], r9d

loop instruct
ret