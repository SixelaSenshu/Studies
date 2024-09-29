.global _start
.section .text
_start: 
	// syscall(write:4, fd=1, buf="hello world!", 13)
	xor %ebx, %ebx
	inc %ebx 
	lea 10(%ebx), %eax 
	movl $0, %ecx
	movl $0, %edx
	jmp msg
next:
	pop %ebx 
	int $0x80 
	xor %eax, %eax 
	inc %al
	int $0x80
msg:
	call next
.asciz "/bin/sh"
