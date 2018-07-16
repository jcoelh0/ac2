	.data

msg1:	.asciiz "Pedro Miguel André Coelho Nº 68803"

	.text
	.globl main

main:	la $a0,msg1
	li $v0,8
	syscall

while:	li $v0,2
	syscall

	beq $v0,'\n',end

	move $a0,$v0
	li $v0,3
	syscall

	j while

end:	li $v0,1
	jr $ra
