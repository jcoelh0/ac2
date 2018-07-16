	.equ RESET_CORE_TIMER,12
	.equ READ_CORE_TIMER,11
	
	.data
	.text
	.globl main

main:

for:	ble $a0,0,end

	li $v0,RESET_CORE_TIMER
 	syscall 		# resetCoreTimer();

while: 	li $v0,READ_CORE_TIMER
	syscall
       	blt $v0,20000,while
	
	sub $a0,$a0,1
	j for

end:	jr $ra
