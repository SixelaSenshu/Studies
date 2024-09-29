.section .data
x:
    .long 10
buffer:
    .asciz 

len:
    .long 32


.section .text
.global main

print:
    pushq %rbp
    movq %rsp, %rbp
    popq %rbp
    ret


blob:
    pushq %rbp
    movq %rsp, %rbp
    movl x, %eax
    pushq %rax
    movl 8(%rsp), %eax
    pushq %rax
    popq %rax
    popq %rbx
    addl %ebx, %eax
    pushq %rax
    movl %eax, x
    popq %rax
    movl x, %eax
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
    movl $1,%eax
    # free(x)
    pushq %rax
    call blob
    movq %rax, buffer
    call console_log

    movl $2,%eax
    pushq %rax
    call blob
    movq %rax, buffer
    call console_log

    movl $60, %eax
    xor %edi, %edi
    syscall
