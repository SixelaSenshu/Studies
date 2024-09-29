.section .data
global:
    .long 10
buffer:
    .asciz 

len:
    .long 32


.section .text
.global main

externe:
    pushq %rbp
    movq %rsp, %rbp

interne:
    pushq %rbp
    movq %rsp, %rbp
    movl 8(%rsp), %eax
    pushq %rax
    movl 16(%rsp), %eax
    pushq %rax
    popq %rax
    popq %rbx
    addl %ebx, %eax
    pushq %rax
    popq %rax
    popq %rbp
    ret

    popq %rax
    movl , %eax
    popq %rbp
    ret


console_log:
    movq $1, %rax
    movq $1, %rdi
    movq buffer, %rsi
    movq $len, %rdx
    syscall
    ret

main:
    movl global, %eax
    pushq %rax
    # free(global)
    popq %rax
    popq %rbx
    addl %ebx, %eax
    pushq %rax
    movl $12,%eax
    pushq %rax
    call f
    movq %rax, buffer
    call console_log

    movl $60, %eax
    xor %edi, %edi
    syscall
