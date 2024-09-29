.section .data
x:
    .long 0
y:
    .long 0
buffer:
    .asciz 

len:
    .long 32


.section .text
.global main

console_log:
    movq $1, %rax
    movq $1, %rdi
    movq buffer, %rsi
    movq $len, %rdx
    syscall
    ret

main:
    #ERROR: Type NullLiteral 
    movl $0,%eax

    popq %rax
    popq %rbx
    andl %ebx, %eax
    pushq %rax

    popq %rax
    popq %rbx
    andl %ebx, %eax
    pushq %rax

    movl $1,%eax
    pushq %rax
    movl $0,%eax
    pushq %rax
    popq %rax
    popq %rbx
    movl %eax, %edx
    idivl %ebx
    pushq %rax

    incl x
    movl x, %eax
    pushq %rax
    # free(x)
    incl x
    movl x, %eax
    pushq %rax
    popq %rax
    popq %rbx
    addl %ebx, %eax
    pushq %rax

    incl y
    movl y, %eax
    pushq %rax
    # free(y)
    incl y
    movl y, %eax
    pushq %rax
    popq %rax
    popq %rbx
    addl %ebx, %eax
    pushq %rax

    # ERROR: Variable z not declared
    movl $0, %eax
    pushq %rax

    movl $60, %eax
    xor %edi, %edi
    syscall
