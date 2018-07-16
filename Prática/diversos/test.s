	.data
	.equ SFR_BASE_HI, 0xBF88 # 16 MSbits of SFR area
 	.equ TRISE, 0x6100 # TRISE address is 0xBF886100
 	.equ PORTE, 0x6110 # PORTE address is 0xBF886110
 	.equ LATE, 0x6120 
 	.equ TRISB, 0x6040
 	.equ PORTB, 0x6050
 	.equ LATB, 0x6060
 	.text
	.globl main

main:
	subu $sp,$sp,4
	lw 	$ra,0($sp)
	
	#RE0 a RE3
	
	lui $t1, SFR_BASE_HI 
 	lw $t2, TRISE($t1) 
 	andi $t2, $t2, 0xFFF0
 	sw $t2, TRISE($t1) 
	
	lw $t2, TRISB($t1) 
 	ori $t2, $t2, 0x0001
 	sw $t2, TRISB($t1) 
	
	lw $t2, LATE($t1) 
	andi $t2, $t2, 0xFFF0
 	ori $t2, $t2, 0x0001
 	sw $t2, LATE($t1) 
	
	li $t0,1
while:	
	lw $t4, PORTB($t1)
	andi $t4,$t4,0x000F
	beq $t4,1,oito
	
	li	$a0,100
	j	fin
oito:
	li	$a0,800	
fin:jal delay
	
	
	lw	$t2, LATE($t1)
	
	andi $t3,$t2,0x000F
	beq $t3,0x0008,decres
	j	other
decres:
	li $t0,0
	j	end	
other:
	beq $t3,0x0001,cres
	j	end
cres:	
	li	$t0,1
end:
	
	beq $t0,1,cresce
	j	decresce
cresce:
	sll $t2, $t2, 1
	j	final

decresce:
	srl	$t2,$t2,1	
final:	
	sw 	$t2, LATE($t1)
		

	j	while
	
	
	sw	$ra,0($sp)
	addu $sp,$sp,4
	jr	$ra
	
	
delay:	
ford:	beqz $a0, endfd

		li 	$v0, 12
 		syscall 					# resetCoreTimer();
 		
whiled:	li 	$v0, 11 	
 		syscall 				
				
 		blt $v0, 20000, whiled 		# while(readCoreTimer() < 20000);
 		
 		sub $a0, $a0, 1
	 	j 	ford					# }
endfd:
 		jr 	$ra 					#
