#Chase Brown
#Output Number from Memory

	.text
	.globl	_main
	
_main:

#	Num to output: 1235
	mov		$1235, %esi
	mov		$33, %ebx
	mov		$1, %edi
	ror 	%edi	
	
topBinary:

	sub		$1, %ebx
	jz 		doneBinary
	mov	 	%esi, %edx
	and 	%edi, %edx
	mov		$'0', %ecx
	jz		out0

out1:

#	Turns '0' to '1'
	inc		%ecx

out0:

	sub 	$32, %eax
	push 	ecx
	call	_putchar
	add 	$32, %eax
	shr		%edi
	jmp 	topBinary

doneBinary:

#	Prints New Line
	push	$10
	call 	_putchar
	push	$13
	call	_putchar

topHex:
	
	xor 	%eax, %eax	# init registers
	xor 	%ebx, %ebx
	xor 	%ecx, %ecx
	xor 	%edx, %edx	
	xor 	%edi, %edi	
	mov 	%esi, %eax	# Moves 1235 to EAX
	mov 	$16, %ebx	# Hex value into ECX

	.data
string:		.asciz	"          "	
	.text
	lea		string, %ecx
	mov		$9, %edi
	
loop:
	xor 	%edx, %edx
	cmp 	$0, %eax
	je 		outHex
	div 	%ebx
	call 	asciiChar
	mov 	%dl, (%ecx, %edi)
	dec 	%edi
	jnz 	loop
	
outHex:	

	sub 	$48, %esp
	call 	_puts
	add		$48, %esp

asciiChar:
	add		$'0', %dl
	cmp		$'9', %dl
	jle 	done
	add 	$7, %dl

done:	
	ret
	.section .rodata
