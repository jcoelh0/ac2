        .equ SFR_BASE_HI, 0xBF88      # 16 MSbits of SFR area 
        .equ TRISE, 0x6100            # TRISE address is 0xBF886100
        .equ PORTE, 0x6110            # PORTE address is 0xBF886110
        .equ LATE,  0x6120            # LATE  address is 0xBF886120

	.equ TRISB, 0x6040            
        .equ PORTB, 0x6050           
        .equ LATB,  0x6060            

	.data

msg:	.asciiz "Pedro Miguel André Coelho Nº 68803"

	.text
	.globl main

main:	subu $sp, $sp, 4
	sw $ra, 0($sp)

	la $a0, msg
	li $v0, 8
	syscall

	# Configurar RE0 a RE3 como saídas
      	lui $t0, SFR_BASE_HI  
      	lw $t1, TRISE($t0)
      	andi $t1, $t1, 0xFFF0
      	sw $t1, TRISE($t0)

	# Configurar RB0 a RB3 como entradas 
      	lw $t1, TRISB($t0)
      	ori $t1, $t1, 0x000F
      	sw $t1, TRISB($t0)

	li $t3, 0  # Contador = 0;

while:	lw $t2, LATE($t0)
	andi $t2, $t2, 0xFFF0

	addi $t3, $t3, 1
	andi $t3, $t3, 0x000F

	or $t2, $t2, $t3
	sw $t2, LATE($t0)
	
	li $a0, 500
	jal delay

	j while

	lw $ra, 0($sp)
	addu $sp, $sp, 4

	jr $ra

delay:	

for:	ble $a0,0,end
	
	li $v0, 12
	syscall

while1:	li $v0, 11
	syscall

	blt $v0,20000,while1	

	sub $a0, $a0, 1
	j for

end:	jr $ra
