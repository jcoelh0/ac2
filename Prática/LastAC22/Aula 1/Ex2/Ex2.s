	.data

msg:	.asciiz "Pedro Miguel André Coelho Nº 68803"
msg2:	.asciiz "Key pressed\n"

	.text
	.globl main

main:	la $a0,msg
	li $v0,8
	syscall

while1:	li $v0,1
	syscall
	beq $v0,$0,while1

	beq $v0,'\n',end
	
	la $a0,msg2
	li $v0,8
	syscall

	j while1

end:	li $v0,0
	jr $ra
