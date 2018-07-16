	.data

msg1:	.asciiz "Pedro Miguel André Coelho Nº 68803"
msg2:	.asciiz "\nIntroduza um número (sinal e módulo): "
msg3:	.asciiz "\nValor lido em base 2: "
msg4:	.asciiz "\nValor lido em base 16: "
msg5:	.asciiz "\nValor lido em base 10 (unsigned): "
msg6:	.asciiz "\nValor lido em base 10 (signed): "

	.text
	.globl main

main:	la $a0,msg1
	li $v0,8
	syscall

while:	la $a0,msg2
	li $v0,8
	syscall

	li $v0,5  # readInt10();
	syscall

	move $t0,$v0

	la $a0,msg3
	li $v0,8
	syscall

	move $a0,$t0  # Base 2
	li $a1,2
	li $v0,6
	syscall

	la $a0,msg4
	li $v0,8
	syscall

	move $a0,$t0  # Base 16
	li $a1,16
	li $v0,6
	syscall

	la $a0,msg5
	li $v0,8
	syscall

	move $a0,$t0  # Base 10 (unsigned)
	li $a1,10
	li $v0,6
	syscall

	la $a0,msg6
	li $v0,8
	syscall

	move $a0,$t0  # Base 10 (signed)
	li $v0,7
	syscall

	j while	

	jr $ra
