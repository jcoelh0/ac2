	.equ SFR_BASE_HI, 0xBF88      # 16 MSbits of SFR area 
	.equ TRISE, 0x6100            # TRISE address is 0xBF886100
	.equ PORTE, 0x6110            # PORTE address is 0xBF886110
	.equ LATE,  0x6120            # LATE  address is 0xBF886120

      	.equ SFR_BASE_HI, 0xBF88      # 16 MSbits of SFR area 
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

	lui $t0, SFR_BASE_HI  
     	lw $t1, TRISE($t0)      
      	andi $t1, $t1, 0xFFFE    
      	sw $t1, TRISE($t0)

	lw $t2, TRISB($t0)
	ori $t2, $t2, 0x0001
	sw $t2, TRISB($t0)

while:	lw $t3, PORTB($t0)
	andi $t3,$t3,0x0001   # opens bit RB0
	
	lw $t4,LATE($t0)
	andi $t4,$t4,0xFFFE    # clears LATEx
	
	or $t4,$t4,$t3	      # LATE0 = RB0
	sw $t4,LATE($t0)

	j while

	jr $ra
