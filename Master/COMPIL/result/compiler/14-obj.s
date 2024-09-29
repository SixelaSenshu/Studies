.section .data
ken0:
    ken0_nom:
      .string "Ken Jones"
    ken0_age:
      .long 39
    ken0_surnom:
      .string "Kenny"
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
    # free(ken0)
    movl $60, %eax
    xor %edi, %edi
    syscall
