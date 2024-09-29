.section .data
rand_string0:
      .string "Rand McNally"
rand_string2:
      .string "Randy"
ken_string0:
      .string "Ken Jones"
ken_string2:
      .string "Kenny"
buffer:
    .asciz 

len:
    .long 32

.section .bss
rand: .skip 32
ken: .skip 32

.section .text
.global main

Personne:
    pushq %rbp
    movq %rsp, %rbp
    popq %rax
    movl %eax, 8(%rdi)
    popq %rax
    movl %eax, 16(%rdi)
    popq %rax
    movl %eax, 24(%rdi)
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
    movl rand_string0, %eax
    pushq %rax
    movl $33, %eax
    pushq %rax
    movl rand_string2, %eax
    pushq %rax
    movq rand,%rdi
    call Personne
    movl ken_string0, %eax
    pushq %rax
    movl $39, %eax
    pushq %rax
    movl ken_string2, %eax
    pushq %rax
    movq ken,%rdi
    call Personne
    movl $60, %eax
    xor %edi, %edi
    syscall
