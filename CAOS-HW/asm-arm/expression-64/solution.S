.text 
.global f

f: 
    mul     x0, x0, x3 // A*x
    mul     x0, x0, x3 // A*x*x
    mul     x1, x1, x3 // B*x
    add     x0, x0, x1 // A*x^2 + B*x
    add     x0, x0, x2 // A*x^2 + B*x + C
    ret