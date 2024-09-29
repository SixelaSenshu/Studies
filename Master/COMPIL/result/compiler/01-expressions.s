.section .data
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
    movl $1,%eax
    pushq %rax

    movl $1,%eax
    pushq %rax
    movl $2,%eax
    pushq %rax
    popq %rax
    popq %rbx
    addl %ebx, %eax
    pushq %rax

    movl $1,%eax
    pushq %rax
    movl $2,%eax
    pushq %rax
    popq %rax
    popq %rbx
    addl %ebx, %eax
    pushq %rax
    movl $3,%eax
    pushq %rax
    popq %rax
    popq %rbx
    addl %ebx, %eax
    pushq %rax

    movl $1,%eax
    pushq %rax
    movl $2,%eax
    pushq %rax
    movl $3,%eax
    pushq %rax
    popq %rax
    popq %rbx
    imull %ebx, %eax
    pushq %rax
    popq %rax
    popq %rbx
    addl %ebx, %eax
    pushq %rax

    movl $1,%eax
    pushq %rax
    movl $2,%eax
    pushq %rax
    popq %rax
    popq %rbx
    addl %ebx, %eax
    pushq %rax
    movl $3,%eax
    pushq %rax
    popq %rax
    popq %rbx
    imull %ebx, %eax
    pushq %rax

    movl $1,%eax
    pushq %rax
    movl $2,%eax
    pushq %rax
    popq %rax
    popq %rbx
    imull %ebx, %eax
    pushq %rax
    movl $3,%eax
    pushq %rax
    popq %rax
    popq %rbx
    addl %ebx, %eax
    pushq %rax

    movl $1,%eax
    pushq %rax
    movl $2,%eax
    pushq %rax
    movl $3,%eax
    pushq %rax
    popq %rax
    popq %rbx
    imull %ebx, %eax
    pushq %rax
    popq %rax
    popq %rbx
    addl %ebx, %eax
    pushq %rax
    movl $4,%eax
    pushq %rax
    popq %rax
    popq %rbx
    addl %ebx, %eax
    pushq %rax

    movl $60, %eax
    xor %edi, %edi
    syscall
