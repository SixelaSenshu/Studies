.section .data
x:
    .long 123
buffer:
    .asciz 

len:
    .long 32


.section .text
.global main

testSwitch:
    pushq %rbp
    movq %rsp, %rbp
    movl $12345678, %eax
    popq %rbp
    ret
    popq %rbp
    ret


neg:
    pushq %rbp
    movq %rsp, %rbp
    popq %rbp
    ret


testSwitchEvil:
    pushq %rbp
    movq %rsp, %rbp
    movl $12345678, %eax
    popq %rbp
    ret
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
    # free(x)
    movl $1234,%eax
    pushq %rax
    call testSwitch
    movq %rax, buffer
    call console_log

    movl $1235,%eax
    pushq %rax
    call testSwitch
    movq %rax, buffer
    call console_log

    movl $124,%eax
    pushq %rax
    call testSwitchEvil
    movq %rax, buffer
    call console_log

    call testSwitchEvil
    movq %rax, buffer
    call console_log

    movl $60, %eax
    xor %edi, %edi
    syscall
