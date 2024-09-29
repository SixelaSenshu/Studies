.section .data
x:
    .long 0
y:
    .long 8
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


console_log:
    movq $1, %rax
    movq $1, %rdi
    movq buffer, %rsi
    movq $len, %rdx
    syscall
    ret

main:
main_WHILE_0:
    movl $10, %ebx
    movl x, %ecx
    cmpl %ecx,%ebx
    jl main_WHILE_END_0
    movl x, %ebx
    movl y, %ecx
main_IF_0:
    cmpl %ebx,%ecx
    je  main_IF_CONS_0
    jmp main_ELSE_CONS_0
main_IF_CONS_0:
    jmp main_WHILE_END_0
    jmp main_IF_END_0
main_ELSE_CONS_0:
main_IF_END_0:

    incl x
    movl x, %ebx
    movl $2, %ecx
main_IF_1:
    cmpl %ebx,%ecx
    jl main_IF_CONS_1
    jmp main_ELSE_CONS_1
main_IF_CONS_1:
    jmp main_IF_END_1
main_ELSE_CONS_1:
main_IF_END_1:

    movl x, %eax
    pushq %rax
    movq %rax, buffer
    call console_log
    jmp main_WHILE_0
main_WHILE_END_0:

    # free(y)
    # free(x)
    movl $60, %eax
    xor %edi, %edi
    syscall
