	.equ SFR_BASE_HI, 0xBF88      # 16 MSbits of SFR area 
	.equ TRISE, 0x6100            # TRISE address is 0xBF886100
	.equ PORTE, 0x6110            # PORTE address is 0xBF886110
	.equ LATE,  0x6120            # LATE  address is 0xBF886120

      	.equ TRISB, 0x6040            # TRISE address is 0xBF886100
      	.equ PORTB, 0x6050            # PORTE address is 0xBF886110
      	.equ LATB,  0x6060            # LATE  address is 0xBF886120

	.data

msg:	.asciiz "Pedro Miguel André Coelho Nº 68803"

	.text
	.globl main

main:	la $a0, msg
	li $v0,8
	syscall

	# RE0 a RE3 como saídas
	lui $t0, SFR_BASE_HI   
      	lw $t1, TRISE($t0)   
      	andi $t1, $t1, 0xFFF0     
      	sw $t1, TRISE($t0)  

	# RB0 a RB3 como entradas
      	lw $t1, TRISB($t0)   
      	ori $t1, $t1, 0x000F     
      	sw $t1, TRISB($t0)  

while:	# RE0 = RB0\
	lw $t2, PORTB($t0)
	xori $t2, $t2, 0x0001
	andi $t2, $t2, 0x0001
	lw $t3, LATE($t0)
	andi $t3, $t3, 0xFFFE
	or $t3, $t3, $t2
	sw $t3, LATE($t0)


	# RE1 = RB1
	lw $t4, PORTB($t0)
	andi $t4, $t4, 0x0002
	lw $t5, LATE($t0)
	andi $t5, $t5, 0xFFFD
	or $t5, $t5, $t4
	sw $t5, LATE ($t0)

	
	# RE2 = RB2
	lw $t6, PORTB($t0)
	andi $t6, $t6, 0x0004
	lw $t7, LATE($t0)
	andi $t7, $t7, 0x000B
	or $t7, $t7, $t6
	sw $t7, LATE($t0)


	# RE3 = RB3\
	lw $t8, PORTB($t0)
	xori $t8, $t8, 0x0008
	andi $t8, $t8, 0x0008
	lw $t9, LATE($t0)
	andi $t9, $t9, 0x0007
	or $t9, $t9, $t8
	sw $t9, LATE($t0)

	j while

	jr $ra
