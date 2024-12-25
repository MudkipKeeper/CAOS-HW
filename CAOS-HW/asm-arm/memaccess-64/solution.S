.global sum
.text

sum:
    mov x8, 0
    mov x9, 0
LoopBegin:
    cmp x8, x1
    bge LoopEnd
    ldr x10, [x2, x9]
    add x9, x9, 4
    add x8, x8, 1
    add x0, x0, x10
    b   LoopBegin    
LoopEnd:
    ret