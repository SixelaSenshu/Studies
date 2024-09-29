.section .data
buffer:
    .asciz 

len:
    .long 32


.section .text
.global main



factorial:
    pushq %rbp
    movq %rsp, %rbp
    movl 8(%rsp), %eax
    pushq %rax
    movl $0,%eax
    pushq %rax
    popq %rax
    popq %rbx
    cmpl %ebx, %eax
    sete %al
    movzbl %al, %eax
    pushq %rax
    popq %rax
    movl %eax,%ebx
    movl 8(%rsp), %eax
    pushq %rax
    movl $1,%eax
    pushq %rax
    popq %rax
    popq %rbx
    cmpl %ebx, %eax
    sete %al
    movzbl %al, %eax
    pushq %rax
    popq %rax
    movl %eax,%ecx
main_IF_0:
    orl %ebx, %ecx
    cmpl $1, %ecx
    je main_IF_CONS_0
    jmp main_ELSE_CONS_0
main_IF_CONS_0:
    movl $1, %eax
    popq %rbp
    ret
    jmp main_IF_END_0
main_ELSE_CONS_0:
main_IF_END_0:

    movl 8(%rsp), %eax
    pushq %rax
    call factorial
    popq %rax
    popq %rbx
    imull %ebx, %eax
    pushq %rax
    popq %rax
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
    movl $3,%eax
    pushq %rax
    call factorial

    movl $60, %eax
    xor %edi, %edi
    syscall
