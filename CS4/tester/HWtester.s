message:
	.ascii "Hello World\0"	
	.text
	.globl	_main
_main:
	mov		%esp, %ebp
	sub		$32, %esp
	call	___main
	lea		message(%esi), %ecx
	call	_puts
	mov		$0, %eax
	add		$32, %esp
	ret
	.section .rodata
