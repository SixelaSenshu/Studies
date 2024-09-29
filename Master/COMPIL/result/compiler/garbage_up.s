.section .data
a:
    .long 1
b:
    .long 2
c:
    .long 3
d:
    .long 5
e:
    .long 6
i:
    .long 2
j:
    .long 3
k:
    .long 4
y:
    .long 5
dic:
    dic_x:
      .long 1
    dic_y:
      .long 2
    dic_z:
      .long 3
dic2:
    dic2_x:
      .long 1
    dic2_y:
      .long 2
    dic2_z:
      .long 3
buffer:
    .asciz 

len:
    .long 32


.section .text
.global main

add:
    pushq %rbp
    movq %rsp, %rbp
    movl a, %eax
    pushq %rax
    movl 8(%rsp), %eax
    pushq %rax
    popq %rax
    popq %rbx
    addl %ebx, %eax
    pushq %rax
    popq %rax
    popq %rbp
    ret


subtract:
    pushq %rbp
    movq %rsp, %rbp
    movl a, %eax
    pushq %rax
    movl 8(%rsp), %eax
    pushq %rax
    popq %rax
    popq %rbx
    subl %ebx, %eax
    pushq %rax
    popq %rax
    popq %rbp
    ret


add2:
    pushq %rbp
    movq %rsp, %rbp
    movl 8(%rsp), %eax
    pushq %rax
    popq %rax
    popq %rbx
    addl %ebx, %eax
    pushq %rax
    movl 24(%rsp), %eax
    pushq %rax
    popq %rax
    popq %rbx
    addl %ebx, %eax
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
    # free(dic2)
    # free(k)
    movl y, %eax
    pushq %rax
    # free(y)
    movl $0, c

    addl $1, d

    addl $2, j

    movl a, %eax
    pushq %rax
    movl b, %eax
    pushq %rax
    call add

    movl a, %eax
    pushq %rax
    movl b, %eax
    pushq %rax
    popq %rax
    popq %rbx
    addl %ebx, %eax
    pushq %rax
    movl %eax, c

    movl a, %eax
    pushq %rax
    movl $2,%eax
    pushq %rax
    popq %rax
    popq %rbx
    addl %ebx, %eax
    pushq %rax
    movl %eax, c

    movl $c, a

    movl a, %eax
    pushq %rax
    movl b, %eax
    pushq %rax
    call subtract
    movq %rax, buffer
    call console_log

    incl b

    #ERROR: Type NullLiteral 
    movl $0,%eax

    movl a, %ebx
    movl b, %ecx
main_IF_0:
    cmpl %ebx,%ecx
    jg  main_IF_CONS_0
    jmp main_ELSE_CONS_0
main_IF_CONS_0:
    movl a, %eax
    pushq %rax
    movq %rax, buffer
    call console_log
    jmp main_IF_END_0
main_ELSE_CONS_0:
    movl b, %eax
    pushq %rax
    movq %rax, buffer
    call console_log
main_IF_END_0:

    movl dic_x,%eax
    # free(dic)
    movq %rax, buffer
    call console_log

main_FOR_0:
    movl $10, %ebx
    movl i, %ecx
    cmpl %ecx,%ebx
    jl main_FOR_END_0
    movl i, %eax
    pushq %rax
    movq %rax, buffer
    call console_log
    incl i
    jmp main_FOR_0
main_FOR_END_0:

    movl a, %ebx
    movl b, %ecx
main_IF_1:
    cmpl %ebx,%ecx
    jg  main_IF_CONS_1
    jmp main_ELSE_CONS_1
main_IF_CONS_1:
    movl a, %eax
    pushq %rax
    movq %rax, buffer
    call console_log
    movl a, %ebx
    movl c, %ecx
main_IF_1:
    cmpl %ebx,%ecx
    jg  main_IF_CONS_1
    jmp main_ELSE_CONS_1
main_IF_CONS_1:
    movl c, %eax
    pushq %rax
    movq %rax, buffer
    call console_log
    jmp main_IF_END_1
main_ELSE_CONS_1:
    movl b, %eax
    pushq %rax
    movq %rax, buffer
    call console_log
main_IF_END_1:

    jmp main_IF_END_1
main_ELSE_CONS_1:
main_IF_END_1:

    # free(i)
    # free(b)
    movl $1,%eax
    pushq %rax
    movl $2,%eax
    pushq %rax
    movl c, %eax
    pushq %rax
    call add2

    movl $7, e
    # free(e)

    movl $2, j
    # free(j)

    movl $c, c
    # free(c)

    addl $a, d
    # free(d)
    # free(a)

    movl $60, %eax
    xor %edi, %edi
    syscall
