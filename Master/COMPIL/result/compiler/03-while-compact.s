.section .data
x:
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
main_WHILE_0:
    movl $10, %ebx
    movl x, %ecx
    cmpl %ecx,%ebx
    jl main_WHILE_END_0
    incl x
    movl x, %eax
    pushq %rax
    movq %rax, buffer
    call console_log
    jmp main_WHILE_0
main_WHILE_END_0:

    # free(x)
    movl $60, %eax
    xor %edi, %edi
    syscall
